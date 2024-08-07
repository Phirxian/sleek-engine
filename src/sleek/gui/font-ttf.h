#ifndef GUI_FONT_TTF
#define GUI_FONT_TTF

#include "font.h"
#include <vector>
#include <map>

class FT_LibraryRec_;
typedef struct FT_LibraryRec_  *FT_Library;

class FT_FaceRec_;
typedef struct FT_FaceRec_*  FT_Face;

namespace sleek
{
    namespace gui
    {
        class interface;
        class frame;

        class font_ttf : public font
        {
            struct CachedGlyph
            {
                std::vector<u8> bitmap;
                int width;
                int height;
                int bearingX;
                int bearingY;
                int advance;
            };

            public:
                font_ttf(interface*, void*, int) noexcept;
                font_ttf(interface*, const std::string &ttf) noexcept;
                ~font_ttf();

                math::vec2i getTextDimensions(const std::string& text, int font_size);

                virtual std::shared_ptr<driver::texture> build(const std::string &, int font_size) noexcept;

            protected:
                void cacheGlyph(int size, int c);
                void draw(std::shared_ptr<driver::texture> buffer, const std::string& text, int font_size, math::vec2i padding);

            private:
                // font size << 8 + character
                std::map<int, CachedGlyph> glyph_cache;
                FT_Library library;
                FT_Face face;
        };
    }
}

#endif
