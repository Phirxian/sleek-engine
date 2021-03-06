#ifndef GUI_STATICTEXT
#define GUI_STATICTEXT

#include "frame.h"

namespace sleek
{
    namespace gui
    {
        class statictext : public frame
        {
            public:
                statictext(interface*) noexcept;
                ~statictext() noexcept;
                virtual INTERFACE_GUI_CODE getType() const noexcept { return IGT_STATICTEXT; }

                virtual void setText(const std::string &t) noexcept;
                virtual void setFont(std::shared_ptr<font>) noexcept;

                virtual void UpdateFontPos() noexcept;

                virtual bool manage(device::input*) noexcept;

                virtual void render() noexcept;
            private:
                bool isHovored;
        };
    }
}

#endif
