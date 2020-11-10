#include "interface.h"
#include "picture.h"

namespace sleek
{
    namespace gui
    {
        picture::picture(interface *m) noexcept : frame(m), pic(0)
        {
            isHovored = false;
        }

        picture::~picture() noexcept
        {
        }

        void picture::setTexture(std::shared_ptr<driver::texture> i) noexcept
        {
            pic = i;
            if(pic)
                box.setSizeFromUpperLeft(i->getDimension());
        }

        bool picture::manage(device::input *e) noexcept
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
                    gui::IET_PICTURE_HOVORED :
                    gui::IET_PICTURE_FOCUSED;
                return true;
            }
        }

        std::shared_ptr<driver::texture> picture::getTexture() const noexcept
        {
            return pic;
        }

        void picture::render() noexcept
        {
            if(!pic) return;
            mom->getDrawManager()->setActiveMaterial(rnd);
            mom->getDrawManager()->drawTexture(pic.get(), box.getUpperLeft());
        }
    }
}
