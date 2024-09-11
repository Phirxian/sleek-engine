#include "../interface.h"
#include "font.h"

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
