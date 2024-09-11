#include "../interface.h"
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

            hovored = box.intersect(e->mouse_pos);

            if(e->type == device::EVENT_MOUSSE_UP && e->mouse[device::MOUSE_LEFT])
            {
                if(hovored && pushed)
                {
                    mom->setActiveFrame(this);
                    pushed = false;
                    e->gui.called = this;
                    e->gui.code = gui::IET_BUTTON_CLICKED;
                    return true;
                }
                
                pushed = false;
            }

            pushed = e->key_state[device::KEY_LBUTTON] && hovored;

            // Handle key events for active frame
            if (mom->getActiveFrame() == this)
            {
                pushed = e->key_state[device::KEY_SPACE];
                std::cout << this << " " << pushed << std::endl;

                if (e->type == device::EVENT_KEY_UP && e->key[device::KEY_SPACE])
                {
                    pushed = false;
                    e->gui.called = this;
                    e->gui.code = gui::IET_BUTTON_CLICKED;
                    return true;
                }
            }
            
            // Notify about state changes
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

            if(pushed)
                mom->getTheme()->drawButtonPushed(this);
            else if(hovored)
                mom->getTheme()->drawButtonHovored(this);
            else
                mom->getTheme()->drawButton(this);

            mom->getTheme()->drawFont(this);
            renderChild();
        }
    }
}
