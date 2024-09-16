#ifndef GUI_FONT
#define GUI_FONT

#include "../../driver/texture.h"
#include "../../math/aabbox.h"

namespace sleek
{
    namespace gui
    {
        class Interface;
        class frame;

        class font : public std::enable_shared_from_this<font>
        {
            public:
                font(Interface*) noexcept;

                inline std::shared_ptr<font> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual std::shared_ptr<driver::texture> build(const std::wstring &, int font_size) noexcept = 0;
                
                std::string getFilename() const noexcept;
            protected:
                Interface *mom;
                std::string file;
        };
    }
}

#endif
