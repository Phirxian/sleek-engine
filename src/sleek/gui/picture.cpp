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
            isScalable = true;
        }

        picture::~picture() noexcept
        {
        }

        void picture::setScalable(bool i) noexcept
        {
            isScalable = i;
        }

        bool picture::getScalable() const noexcept
        {
            return isScalable;
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

            auto size = box.getSize();
            auto scl = box.getSize();
            
            if (!isScalable)
            {
                if (aspect > 1)
                    scl.x = scl.y * aspect;
                else
                    scl.y = scl.x / aspect;
            }

            frame::render();
            
            mom->getDrawManager()->setActiveMaterial(mom->getTheme()->getSolidMaterial());

            mom->getDrawManager()->pushScissor(box.grow(1));
            mom->getDrawManager()->drawTextureScale(
                pic.get(),
                {
                    box.getUpperLeft().x + (size.x-scl.x)/2,
                    box.getUpperLeft().y + (size.y-scl.y)/2 +1
                },
                {0, 0, 0},
                {scl.x-2, scl.y-2, 0},
                {1.f, 1.f}
            );
            mom->getDrawManager()->clearScissor();
        }
    }
}
