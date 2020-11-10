#include "interface.h"
#include "font.h"

//#include <ft2build.h>
//#include FT_FREETYPE_H

namespace sleek
{
    namespace gui
    {
        font::font(interface *i, void *buffer, int buffersize) noexcept
            : mom(i)
        {
//            FT_Init_FreeType(&library);
//            FT_New_Memory_Face(library, (FT_Byte*)buffer, buffersize, 0, &face);
        }

        font::font(interface *i, const std::string &ttf) noexcept
            : mom(i), file(ttf)
        {
//            FT_Init_FreeType(&library);
//            FT_New_Face(library, ttf.c_str(), 0, &face);
        }

        font::~font() noexcept
        {
        }

        std::string font::getFilename() const noexcept
        {
            return file;
        }

        std::shared_ptr<fontcache> font::build(gui::frame *f) noexcept
        {
            auto font = std::make_shared<fontcache>();

//            font->size = math::vec2i(0, 0);
//            FT_GlyphSlot slot = face->glyph;
//
//            for(int i = 0; i<f->getText().size(); ++i)
//            {
//                auto glyph_index = FT_Get_Char_Index(face, f->getText()[i]);
//                FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
//                FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
//                font->size.x += slot->advance.x >> 6;
//                font->size.y += slot->advance.y >> 6;
//            }

            return font;
        }
    }
}
