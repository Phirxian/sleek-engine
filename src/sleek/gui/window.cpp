#include "interface.h"
#include "window.h"

namespace sleek
{
    namespace gui
    {
        window::window(interface *m) noexcept : frame(m)
        {
            title_size = 20;
            isHovored = isMoved = false;

            close = std::make_shared<button>(m);
            close->box = math::aabbox2di(math::vec2i(0,0),math::vec2i(10,10));
            close->move({5, 5});
            close->setParent(this);
            close->UpdateAbsolutePosition();
            close->setText("Close");
        }

        window::~window() noexcept
        {
        }

        button* window::getCloseButton() const noexcept
        {
            return close.get();
        }

        void window::UpdateFontPos() noexcept
        {
            textpos = absolute+relative;

            if(cache)
            {
                textpos.y += cache->size.y+7;
                textpos.x += 12;
            }
        }

        void window::setScale(const math::vec2i &i) noexcept
        {
            frame::setScale(i);
            close->relative = math::vec2i(box.getSize().x-15, 5);
            close->UpdateAbsolutePosition();
        }

        void window::move(const math::vec2i &i) noexcept
        {
            frame::move(i);
            close->relative = math::vec2i(box.getSize().x-15, 5);
            close->UpdateAbsolutePosition();
        }

        bool window::manage(device::input *e) noexcept
        {
            bool CHovored = isHovored, CMoved = isMoved;

            if(frame::manage(e))
            {
                if(e->gui.called == close.get() && e->gui.code == IET_BUTTON_CLICKED)
                {
                    e->clear();
                    e->gui.type = IGT_WINDOW;
                    e->gui.code = IET_WINDOW_CLOSED;
                    mom->removeFrame(getptr());
                }
                return true;
            }

            if(e->type == device::EVENT_MOUSSE_DOWN && e->mouse[device::MOUSE_LEFT] && box.intersect(e->mouse_pos))
            {
                mom->unActiveElement();
                mom->popFrame(getptr());
                isActive = true;
            }


            math::aabbox2di til(
                box.getUpperLeft(),
                math::vec2i(
                    box.getUpperLeft().x+box.getSize().x,
                    box.getUpperLeft().y+title_size
                )
            );

            if(e->type == device::EVENT_MOUSSE_DOWN && e->mouse[device::MOUSE_LEFT] && til.intersect(e->mouse_pos))
                isMoved = true;

            if(e->type == device::EVENT_MOUSSE_UP)
                isMoved = false;

            if(e->type == device::EVENT_MOUSSE_MOVED)
            {
                if(!isMoved)
                {
                    isHovored = box.intersect(e->mouse_pos);
                    def = e->mouse_pos-box.getUpperLeft();
                }
                else
                {
                    relative = math::vec2i();
                    absolute = e->mouse_pos-def;
                    UpdateAbsolutePosition();
                    close->UpdateAbsolutePosition();
                    UpdateFontPos();
                }
            }

            if(isMoved)
            {
                e->gui.called = this;
                e->gui.type = gui::IGT_WINDOW;
                e->gui.code = gui::IET_WINDOW_MOVED;
                return true;
            }

            if(CHovored != isHovored)
            {
                e->gui.called = this;
                e->gui.type = gui::IGT_WINDOW;
                e->gui.code = isHovored ?
                    gui::IET_WINDOW_HOVORED :
                    gui::IET_WINDOW_FOCUSED;
                return true;
            }

            return false;
        }

        void window::render() noexcept
        {
            if(!show) return;

            if(isMoved)
            {
                mom->getTheme()->drawWindowMainMoved(this);
                mom->getTheme()->drawWindowDecorationMoved(this);
                mom->getTheme()->drawWindowTitleMoved(this);
            }
            else if(isHovored)
            {
                mom->getTheme()->drawWindowMainHovored(this);
                mom->getTheme()->drawWindowDecorationHovored(this);
                mom->getTheme()->drawWindowTitleHovored(this);
            }
            else
            {
                mom->getTheme()->drawWindowMain(this);
                mom->getTheme()->drawWindowDecoration(this);
                mom->getTheme()->drawWindowTitle(this);
            }

            mom->getTheme()->drawFont(this);
            close->render();
            renderChild();
        }
    }
}
