#include "../interface.h"
#include "checkbox.h"
#include "button.h"

#include "../../math/function.h"

namespace sleek
{
    namespace gui
    {
        checkbox::checkbox(interface *m) noexcept : frame(m)
        {
            isChecked = false;
            check = std::make_shared<button>(m);
            //check->box = math::aabbox2di(math::vec2i(0,0),math::vec2i(10,10));
            check->move({1, 0});
            check->setParent(this);
            check->setTextSize(10);
            //check->setText(L"\uF00D");
            check->setFont(m->getIconsFont());
        }

        checkbox::~checkbox() noexcept
        {
        }

        void checkbox::UpdateFontPos() noexcept
        {
            auto size = box.getSize();
            // remove the button
            size.x -= size.y;

            textpos = absolute+relative;
            textpos += size/2;
            textpos.x += size.y;

            if(fontcache)
            {
                textpos.x -= fontcache->getDimension().x/2;
                textpos.y -= fontcache->getDimension().y/2 - 2;
            }
        }

        void checkbox::UpdateChildPosition() noexcept
        {
            auto size = box.getSize();
            check->setSize(math::vec2i(size.y, size.y));
            frame::UpdateChildPosition();
        }

        void checkbox::setChecked(const bool i) noexcept
        {
            isChecked = i;

            if (isChecked)
                check->setText(L"\uF00C");
                //check->setText(L"\uF00D");
            else
                check->setText(L"");
        }

        f32 checkbox::getChecked() const noexcept
        {
            return isChecked;
        }

        bool checkbox::manage(device::input *e) noexcept
        {
            if(frame::manage(e))
            {
                if(e->gui.code == IET_BUTTON_CLICKED)
                {
                    if(e->gui.called == check.get())
                    {
                        mom->setActiveFrame(this);
                        setChecked(!getChecked());
                        e->gui.called = this;
                        e->gui.code = gui::IET_CHECKBOX_CHANGED;
                        return true;
                    }
                }
            }

            // override inner button setActiveFrame
            if (e->type == device::EVENT_MOUSSE_UP && e->mouse[device::MOUSE_LEFT])
            {
                if(box.intersect(e->mouse_pos))
                {
                    mom->setActiveFrame(this);
                    setChecked(!getChecked());
                    e->gui.called = this;
                    e->gui.code = gui::IET_CHECKBOX_CHANGED;
                    return true;
                }
            }

            if (mom->getActiveFrame() == this)
            {
                if (e->type == device::EVENT_KEY_UP && e->key[device::KEY_SPACE])
                {
                    setChecked(!getChecked());
                    e->gui.called = this;
                    e->gui.code = gui::IET_CHECKBOX_CHANGED;
                    return true;
                }
            }

            return false;
        }

        void checkbox::render() noexcept
        {
            if(!show) return;
            mom->getTheme()->drawFrame(this);
            mom->getTheme()->drawFont(this);
            renderChild();
        }
    }
}
