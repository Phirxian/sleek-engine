#include "interface.h"
#include "font-ttf.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <algorithm>
#include <cstring>

#define build_key(size, glyphe) (size<<16 | glyphe)

namespace sleek
{
    namespace gui
    {
        font_ttf::font_ttf(interface *i, void *buffer, int buffersize) noexcept
            : font(i)
        {
            FT_Init_FreeType(&library);
            FT_New_Memory_Face(library, (FT_Byte*)buffer, buffersize, 0, &face);
        }

        font_ttf::font_ttf(interface *i, const std::string &ttf) noexcept
            : font(i)
        {
            file = ttf;
            FT_Init_FreeType(&library);
            if(FT_New_Face(library, ttf.c_str(), 0, &face) == 0)
                std::cout << ttf << " loaded" << std::endl;
        }

        font_ttf::~font_ttf() noexcept
        {
            FT_Done_Face(face);
            FT_Done_FreeType(library);
        }

        std::shared_ptr<driver::texture> font_ttf::build(const std::wstring &text, int font_size) noexcept
        {
            math::vec2i padding = {2,2};
            auto size = getTextDimensions(text, font_size);
            auto buffer = std::make_shared<driver::texture>(size+padding*2, driver::TXFMT_RGBA, nullptr);
            std::memset(buffer->getBuffer(), 0, buffer->getBufferSize());
            draw(buffer, text, font_size, padding);
            return buffer;
        }

        void font_ttf::cacheGlyph(int size, int c)
        {
            if(FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cerr << "Error loading glyph" << std::endl;
                return;
            }

            CachedGlyph glyph;
            glyph.width = face->glyph->bitmap.width;
            glyph.height = face->glyph->bitmap.rows;
            glyph.bearingX = face->glyph->bitmap_left;
            glyph.bearingY = face->glyph->bitmap_top;
            glyph.advance = face->glyph->advance.x >> 6;

            glyph.bitmap.assign(
                face->glyph->bitmap.buffer, 
                face->glyph->bitmap.buffer + glyph.width * glyph.height
            );

            long long key = build_key(size, c);
            glyph_cache[key] = glyph;
        }

        math::vec2i font_ttf::getTextDimensions(const std::wstring& text, int font_size)
        {
            FT_Set_Pixel_Sizes(face, 0, font_size);

            int x_size = 0;
            int max_x_size = 0;
            int maxAscender = 0;
            int maxDescender = 0;
            int line_count = 1;

            for(int c : text)
            {
                if(c == '\n')
                {
                    line_count++;
                    max_x_size = std::max(max_x_size, x_size);
                    x_size = 0;
                    continue;
                }

                long long key = build_key(font_size, c);

                if(glyph_cache.find(key) == glyph_cache.end())
                    cacheGlyph(font_size, c);

                const CachedGlyph& glyph = glyph_cache[key];
                x_size += glyph.advance;
                maxAscender = std::max(maxAscender, glyph.bearingY);
                maxDescender = std::max(maxDescender, glyph.height - glyph.bearingY);
            }

            return {
                std::max(max_x_size, x_size),
                (face->glyph->metrics.vertAdvance >> 6)*line_count
            };
        }

        void font_ttf::draw(std::shared_ptr<driver::texture> image, const std::wstring& text, int font_size, math::vec2i padding)
        {
            math::vec2i size = image->getDimension();
            u8 *buffer = image->getBuffer();

            int maxAscent = int(face->ascender * (face->size->metrics.y_scale / 65536.0)) >> 6;
            int maxDescent = int(abs(face->descender * (face->size->metrics.y_scale / 65536.0))) >> 6;

            int x = 0;
            int y = maxAscent - maxDescent;
            int line = 0;

            for(wchar_t c : text)
            {
                if(c == '\n')
                {
                    x = 0;
                    line += face->glyph->metrics.vertAdvance >> 6;
                    continue;
                }

                long long key = build_key(font_size, c);

                if(glyph_cache.find(key) == glyph_cache.end())
                    cacheGlyph(font_size, c);

                const CachedGlyph& glyph = glyph_cache[key];

                for(int row = 0; row < glyph.height; row++)
                {
                    for(int col = 0; col < glyph.width; col++)
                    {
                        int bufferX = x + col + glyph.bearingX;
                        int bufferY = y + row - glyph.bearingY;

                        if(bufferX >= 0 && bufferX < size.x && bufferY >= 0 && bufferY < size.y)
                        {
                            unsigned char pixel = glyph.bitmap[row * glyph.width + col];
                            //buffer[bufferY * size.x + bufferX] = pixel;
                            image->setPixel({bufferX + padding.x, bufferY + line + padding.y}, {pixel, pixel, pixel, pixel});
                        }
                    }
                }

                x += glyph.advance;
            }
        }
    }
}
