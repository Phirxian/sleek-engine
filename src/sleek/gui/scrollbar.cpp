#include "interface.h"
#include "scrollbar.h"

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
            orient = SBO_HORIZONTAL;
            isLeftDown = false;
        }

        scrollbar::~scrollbar() noexcept
        {
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

        void scrollbar::setOrientation(SCROLL_BAR_ORIANTATION i)
        {
            orient = i;
        }

        SCROLL_BAR_ORIANTATION scrollbar::getOrientation()
        {
            return orient;
        }

        void scrollbar::setPercentage(const f32 i) noexcept
        {
            per = i;
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

        bool scrollbar::manage(device::input *e) noexcept
        {
            bool CHovored = isHovored;

            if(frame::manage(e))
                return true;

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

                if(orient == SBO_HORIZONTAL)
                {
                     per = math::clamp(pos.x, box.upperleft.x, box.lowerright.x);
                     per -= box.upperleft.x;
                     per /= float(box.getSize().x);
                }
                else
                {
                     per = math::clamp(pos.y, box.upperleft.y, box.lowerright.y);
                     per -= box.upperleft.y;
                     per /= float(box.getSize().y);
                }

                //std::cout << std::to_string(per) << std::endl;

                e->gui.called = this;
                e->gui.code = gui::IET_SCROLLBAR_UPDATED;
                return true;
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
