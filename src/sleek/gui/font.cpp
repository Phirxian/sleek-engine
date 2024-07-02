#include "interface.h"
#include "font.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <algorithm>
#include <cstring>

namespace sleek
{
    namespace gui
    {
        font::font(interface *i) noexcept
            : mom(i)
        {
        }
        
        std::string font::getFilename() const noexcept
        {
            return file;
        }
    }
}
