#include "interface.h"
#include "button.h"

namespace sleek
{
    namespace gui
    {
        button::button(interface *m) noexcept : frame(m)
        {
            hovored = pushed = false;
        }

        button::~button() noexcept
        {
        }

        bool button::isPushed() const noexcept
        {
            return pushed;
        }

        bool button::isHovored() const noexcept
        {
            return hovored;
        }

        void button::UpdateFontPos() noexcept
        {
            textpos = absolute+relative;
            textpos += box.getSize()/2;

            if(fontcache)
            {
                textpos.x -= fontcache->getDimension().x/2;
                textpos.y -= fontcache->getDimension().y/2 - 2;
            }
        }

        bool button::manage(device::input* e) noexcept
        {
            bool CHovored = hovored;
            bool CPushed = pushed;

            if(frame::manage(e))
            {
                pushed = hovored;
                hovored = false;
                return true;
            }

/*
            if(e->type == device::EVENT_MOUSSE_MOVED)
                hovored = box.intersect(e->mouse_pos);

            if(e->type == device::EVENT_MOUSSE_DOWN && e->mouse[device::MOUSE_LEFT] && hovored)
                pushed = true;
*/

            hovored = box.intersect(e->mouse_pos);
            pushed = e->mouse[device::MOUSE_LEFT] && hovored;

            if(e->type == device::EVENT_MOUSSE_UP && e->mouse[device::MOUSE_LEFT])
            {
                if(hovored && pushed)
                {
                    pushed = false;
                    e->gui.called = this;
                    e->gui.code = gui::IET_BUTTON_CLICKED;
                    return true;
                }
                pushed = false;
            }

            if(CPushed != pushed && pushed)
            {
                e->gui.called = this;
                e->gui.code = gui::IET_BUTTON_PUSHED;
                return true;
            }

            if(CHovored != hovored)
            {
                e->gui.called = this;
                e->gui.code = hovored ?
                    gui::IET_BUTTON_HOVERED :
                    gui::IET_BUTTON_FOCUSED;
                return true;
            }

            return false;
        }

        void button::render() noexcept
        {
            if(!show) return;

            if(hovored && pushed)
                mom->getTheme()->drawButtonPushed(this);
            else if(hovored && !pushed)
                mom->getTheme()->drawButtonHovored(this);
            else
                mom->getTheme()->drawButton(this);

            mom->getTheme()->drawFont(this);
            renderChild();
        }
    }
}
