#include "interface.h"
#include "scrollbar.h"
#include "button.h"

#include "../math/function.h"

namespace sleek
{
    namespace gui
    {
        scrollbar::scrollbar(interface *m) noexcept : frame(m)
        {
            min = 0;
            max = 100;
            per = 0.f;
            step = 5.f;
            orient = SBO_HORIZONTAL;
            isLeftDown = false;

            add = std::make_shared<button>(m);
            add->setParent(this);
            add->setTextSize(10);
            add->setFont(m->getIconsFont());

            sub = std::make_shared<button>(m);
            sub->setSize(math::vec2i(10,10));
            sub->setParent(this);
            sub->setTextSize(10);
            sub->setFont(m->getIconsFont());
            
            setOrientation(SBO_HORIZONTAL);
        }

        scrollbar::~scrollbar() noexcept
        {
        }

        void scrollbar::UpdateChildPosition() noexcept
        {
            auto size = box.getSize();
            auto end = size - sub->getBoundingBox().getSize();

            if (orient == SBO_HORIZONTAL)
            {
                add->move({end.x, 0});
                add->setSize(math::vec2i(size.y, size.y));
                sub->setSize(math::vec2i(size.y, size.y));
            }
            else
            {
                add->move({0, end.y});
                add->setSize(math::vec2i(size.x, size.x));
                sub->setSize(math::vec2i(size.x, size.x));
            }

            frame::UpdateChildPosition();
        }

        void scrollbar::setValue(const s32 i) noexcept
        {
            per = math::clamp(i, min, max)/(max-min);
        }

        void scrollbar::setMin(const s32 i) noexcept
        {
            min = i;
        }

        void scrollbar::setMax(const s32 i) noexcept
        {
            max = i;
        }

        void scrollbar::setStep(const s32 i) noexcept
        {
            step = i;
        }

        void scrollbar::setOrientation(SCROLL_BAR_ORIANTATION i)
        {
            orient = i;
            if(orient == SBO_HORIZONTAL)
            {
                add->setText(L"\uF054");
                sub->setText(L"\uF053");
            }
            else
            {
                add->setText(L"\uF078");
                sub->setText(L"\uF077");
            }
        }

        SCROLL_BAR_ORIANTATION scrollbar::getOrientation()
        {
            return orient;
        }

        void scrollbar::setPercentage(const f32 i) noexcept
        {
            per = math::clamp(i, 0.f, 1.0f);
        }

        f32 scrollbar::getPercentage() const noexcept
        {
            return per;
        }

        s32 scrollbar::getMin() const noexcept
        {
            return min;
        }

        s32 scrollbar::getMax() const noexcept
        {
            return max;
        }

        s32 scrollbar::getValue() const noexcept
        {
            return min + (max-min)*per;
        }

        s32 scrollbar::getStep() const noexcept
        {
            return step;
        }

        bool scrollbar::manage(device::input *e) noexcept
        {
            bool CHovored = isHovored;

            if(frame::manage(e))
            {
                if(e->gui.code == IET_BUTTON_CLICKED)
                {
                    if(e->gui.called == add.get())
                    {
                        setPercentage(getPercentage()+getStep()/100.f);
                        isLeftDown = false;
                        e->gui.called = this;
                        e->gui.code = gui::IET_SCROLLBAR_UPDATED;
                        return true;
                    }

                    if(e->gui.called == sub.get())
                    {
                        setPercentage(getPercentage()-getStep()/100.f);
                        isLeftDown = false;
                        e->gui.called = this;
                        e->gui.code = gui::IET_SCROLLBAR_UPDATED;
                        return true;
                    }
                }
            }

            if(e->type == device::EVENT_MOUSSE_MOVED)
                isHovored = box.intersect(e->mouse_pos);

            if(e->type == device::EVENT_MOUSSE_DOWN)
                isLeftDown = isHovored;

            if(e->type == device::EVENT_MOUSSE_UP)
                isLeftDown = false;

            if(CHovored != isHovored)
            {
                e->gui.called = this;
                e->gui.code = isHovored ?
                    gui::IET_SCROLLBAR_HOVORED :
                    gui::IET_SCROLLBAR_FOCUSED;
                return true;
            }

            if(isLeftDown)
            {
                auto pos = e->mouse_pos;
                auto size = box.getSize();
                auto clickable = box;

                if(orient == SBO_HORIZONTAL)
                {
                    clickable.upperleft.x += size.y;
                    clickable.lowerright.x -= size.y;

                    if (clickable.intersect(pos))
                    {
                        per = math::clamp(pos.x, clickable.upperleft.x, clickable.lowerright.x);
                        per -= clickable.upperleft.x;
                        per /= float(box.getSize().x - 2*size.y);
                        e->gui.called = this;
                        e->gui.code = gui::IET_SCROLLBAR_UPDATED;
                        return true;
                    }
                }
                else
                {
                    clickable.upperleft.y += size.x;
                    clickable.lowerright.y -= size.x;

                    if (clickable.intersect(pos))
                    {
                        per = math::clamp(pos.y, clickable.upperleft.y, clickable.lowerright.y);
                        per -= clickable.upperleft.y;
                        per /= float(box.getSize().y - 2*size.x);
                        e->gui.called = this;
                        e->gui.code = gui::IET_SCROLLBAR_UPDATED;
                        return true;
                    }
                }
            }

            return false;
        }

        void scrollbar::render() noexcept
        {
            if(!show) return;
            mom->getTheme()->drawScrollbar(this);
            renderChild();
        }
    }
}
