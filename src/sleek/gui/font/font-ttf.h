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
        class Interface;
        class frame;

        class font_ttf : public font
        {
            struct CachedGlyph
            {
                std::vector<wchar_t> bitmap;
                int width;
                int height;
                int bearingX;
                int bearingY;
                int advance;
            };

            public:
                font_ttf(Interface*, void*, int) noexcept;
                font_ttf(Interface*, const std::string &ttf) noexcept;
                ~font_ttf();

                math::vec2i getTextDimensions(const std::wstring& text, int font_size);

                virtual std::shared_ptr<driver::texture> build(const std::wstring &, int font_size) noexcept;

            protected:
                void cacheGlyph(int size, int c);
                void draw(std::shared_ptr<driver::texture> buffer, const std::wstring& text, int font_size, math::vec2i padding);

            private:
                // font size << 32 + character
                std::map<long long, CachedGlyph> glyph_cache;
                FT_Library library;
                FT_Face face;
        };
    }
}

#endif
