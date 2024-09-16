#ifndef GUI_THEME
#define GUI_THEME

#include "../driver/driver.h"
#include "../driver/material.h"

namespace sleek
{
    namespace gui
    {
        class button;
        class font;
        class picture;
        class progressbar;
        class statictext;
        class window;
        class scrollbar;

        class theme : public std::enable_shared_from_this<theme>
        {
            public:
                theme(Interface*) noexcept;
                ~theme() noexcept;

                inline std::shared_ptr<theme> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual void drawFont(frame*) const noexcept;

                virtual void drawWindowMain(window*) noexcept;

                virtual void drawWindowDecoration(window*) noexcept;
                virtual void drawWindowDecorationHovored(window*) noexcept;
                virtual void drawWindowDecorationMoved(window*) noexcept;

                virtual void drawWindowTitle(window*) noexcept;
                virtual void drawWindowTitleHovored(window*) noexcept;
                virtual void drawWindowTitleMoved(window*) noexcept;

                virtual void drawButton(button*) noexcept;
                virtual void drawButtonPushed(button*) noexcept;
                virtual void drawButtonHovored(button*) noexcept;
                virtual void drawStaticText(statictext*) noexcept;
                virtual void drawProgressbar(progressbar*) noexcept;
                virtual void drawScrollbar(scrollbar*) noexcept;
                virtual void drawFrame(frame*) noexcept;

                std::shared_ptr<driver::material> getLineMaterial() { return line; }
                std::shared_ptr<driver::material> getSolidMaterial() { return solid; }
                std::shared_ptr<driver::material> getAddMaterial() { return add; }
            protected:
                Interface *mom;
                driver::texture *decor[IGT_COUNT*3];
                std::shared_ptr<driver::material> solid, line, add;
        };
    }
}

#endif
