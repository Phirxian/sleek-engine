#include "interface.h"
#include "progressbar.h"

namespace sleek
{
    namespace gui
    {
        progressbar::progressbar(interface *m) noexcept : frame(m)
        {
            min = 0;
            max = 100;
            per = lst = 0.f;
        }

        progressbar::~progressbar() noexcept
        {
        }

        void progressbar::setValue(const s32 i) noexcept
        {
            lst = per;
            per = i/(max-min);
        }

        void progressbar::setMinValue(const s32 i) noexcept
        {
            min = i;
        }

        void progressbar::setMaxValue(const s32 i) noexcept
        {
            max = i;
        }

        void progressbar::setPercentage(const f32 i) noexcept
        {
            per = i;
        }

        f32 progressbar::getPercentage() const noexcept
        {
            return per;
        }

        s32 progressbar::getMinValue() const noexcept
        {
            return min;
        }

        s32 progressbar::getMaxValue() const noexcept
        {
            return max;
        }

        s32 progressbar:: getValue() const noexcept
        {
            return (max-min)*per;
        }

        bool progressbar::manage(device::input *e) noexcept
        {
            bool CHovored = isHovored;

            if(frame::manage(e))
                return true;

            if(e->type == device::EVENT_MOUSSE_MOVED)
                isHovored = box.intersect(e->mouse_pos);

            if(CHovored != isHovored)
            {
                e->gui.called = this;
                e->gui.code = isHovored ?
                    gui::IET_PROGRESSBAR_HOVORED :
                    gui::IET_PROGRESSBAR_FOCUSED;
                return true;
            }

            if(per != lst)
            {
                e->gui.called = this;
                e->gui.code = gui::IET_PROGRESSBAR_UPDATED;
                return true;
            }

            return false;
        }

        void progressbar::render() noexcept
        {
            if(!show) return;
            mom->getTheme()->drawProgressbar(this);
            renderChild();
        }
    }
}
