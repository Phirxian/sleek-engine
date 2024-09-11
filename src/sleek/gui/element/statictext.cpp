#include "../interface.h"
#include "statictext.h"

namespace sleek
{
    namespace gui
    {
        statictext::statictext(interface *m) noexcept : frame(m)
        {
            isHovored = false;
        }

        statictext::~statictext() noexcept
        {
        }
        
        bool statictext::manage(device::input *e) noexcept
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
                    gui::IET_STATICTEXT_HOVORED :
                    gui::IET_STATICTEXT_FOCUSED;
                return true;
            }

            return false;
        }

        void statictext::render() noexcept
        {
            if(!show) return;
            mom->getTheme()->drawStaticText(this);
            mom->getTheme()->drawFont(this);
            renderChild();
        }
    }
}
