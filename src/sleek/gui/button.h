#ifndef GUI_BUTTON
#define GUI_BUTTON

#include "frame.h"

namespace sleek
{
    namespace gui
    {
        class button : public frame
        {
            public:
                button(interface*) noexcept;
                ~button() noexcept;
                virtual INTERFACE_GUI_CODE getType() const noexcept { return IGT_BUTTON; }

                virtual bool isPushed() const noexcept;
                virtual bool isHovored() const noexcept;

                virtual bool manage(device::input*) noexcept;
                virtual void render() noexcept;
            protected:
                virtual void UpdateFontPos() noexcept;
                bool hovored, pushed;
        };
    }
}

#endif

