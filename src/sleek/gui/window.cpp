#include "interface.h"
#include "window.h"
#include <iostream>

namespace sleek
{
    namespace gui
    {
        window::window(interface *m) noexcept : frame(m)
        {
            title_size = 20;
            isHovored = isMoved = isCollapsed = false;

            close = std::make_shared<button>(m);
            close->box = math::aabbox2di(math::vec2i(0,0),math::vec2i(10,10));
            close->move({5, 5});
            close->setParent(this);
            close->UpdateAbsolutePosition();
            close->setTextSize(10);
            close->setText(L"\uF00D");
            close->setFont(m->getIconsFont());

            collapse = std::make_shared<button>(m);
            collapse->box = math::aabbox2di(math::vec2i(0,0),math::vec2i(10,10));
            collapse->move({20, 5});
            collapse->setParent(this);
            collapse->UpdateAbsolutePosition();
            collapse->setTextSize(10);
            collapse->setText(L"\uF068");
            collapse->setFont(m->getIconsFont());
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
            textpos.x += 50;
            textpos.y += title_size/2;

            if(fontcache)
            {
                textpos.x -= fontcache->getDimension().x/2;
                textpos.y -= fontcache->getDimension().y/2 - 2;
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
                if(e->gui.code == IET_BUTTON_CLICKED)
                {
                    if(e->gui.called == close.get())
                    {
                        e->clear();
                        e->gui.type = IGT_WINDOW;
                        e->gui.code = IET_WINDOW_CLOSED;
                        mom->removeFrame(getptr());
                        return true;
                    }

                    if(e->gui.called == collapse.get())
                    {
                        e->clear();
                        isCollapsed = !isCollapsed;
                        isMoved = false;
                        return true;
                    }
                    // event might be fired by children
                }
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

            if(e->type == device::EVENT_MOUSSE_DOWN && e->mouse[device::MOUSE_LEFT] && box.intersect(e->mouse_pos))
            {
                mom->unActiveElement();
                mom->popFrame(getptr());
                isActive = true;
                return true;
            }

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
                if (!isCollapsed)
                    mom->getTheme()->drawWindowMain(this);
                mom->getTheme()->drawWindowDecoration(this);
                mom->getTheme()->drawWindowTitle(this);
            }
            else if(isHovored)
            {
                if (!isCollapsed)
                    mom->getTheme()->drawWindowMain(this);
                mom->getTheme()->drawWindowDecoration(this);
                mom->getTheme()->drawWindowTitle(this);
            }
            else
            {
                if (!isCollapsed)
                    mom->getTheme()->drawWindowMain(this);
                mom->getTheme()->drawWindowDecoration(this);
                mom->getTheme()->drawWindowTitle(this);
            }

            mom->getTheme()->drawFont(this);

            if (!isCollapsed)
                renderChild();
            else
            {
                close->render();
                collapse->render();
            }
        }
    }
}
