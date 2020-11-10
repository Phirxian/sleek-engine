#ifndef GUI_WINDOW
#define GUI_WINDOW

#include "button.h"

namespace sleek
{
    namespace gui
    {
        class window : public frame
        {
            public:
                window(interface*) noexcept;
                ~window() noexcept;

                virtual INTERFACE_GUI_CODE getType() const noexcept { return IGT_WINDOW; }

                virtual button *getCloseButton() const noexcept;
                virtual void move(const math::vec2i&) noexcept;
                virtual void setScale(const math::vec2i &i) noexcept;

                virtual bool manage(device::input*) noexcept;
                virtual void render() noexcept;
            protected:
                std::shared_ptr<button> close;
                void UpdateFontPos() noexcept;
            private:
                math::vec2i def;
                bool isHovored, isMoved;
                friend class theme;

                u32 title_size;
        };
    }
}

#endif

