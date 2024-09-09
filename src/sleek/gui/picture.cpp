#include "interface.h"
#include "picture.h"

#include <iostream>

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
            
            return frame::manage(e);
        }

        std::shared_ptr<driver::texture> picture::getTexture() const noexcept
        {
            return pic;
        }

        void picture::render() noexcept
        {
            if(!pic)
                return;

            auto aspect = pic->getDimension().x / float(pic->getDimension().y);

            auto scl = box.getSize();
            scl.y = scl.x / aspect;

            frame::render();

            mom->getDrawManager()->setActiveMaterial(mom->getTheme()->getSolidMaterial());

            mom->getDrawManager()->drawTextureScale(
                pic.get(),
                {box.getUpperLeft().x, box.getUpperLeft().y + scl.y/3}, // wtf ?
                {0, 0, 0},
                {scl.x, scl.y, 0},
                {1.f, 1.f}
            );
        }
    }
}
