#include "interface.h"
#include "cursor.h"

namespace sleek
{
    namespace gui
    {
        cursor::cursor(interface *m) noexcept : mom(m)
        {
            isRender = false;
            showCursor(true);
        }

        cursor::~cursor() noexcept
        {
            mom->getDevice()->ShowMouse(true);
        }

        void cursor::setPosition(const math::vec2i &a) noexcept
        {
            mom->getDevice()->WarpMouse(a);
            pos = a;
        }

        void cursor::setTexture(std::shared_ptr<driver::texture> a) noexcept
        {
            tex = a;
        }

        void cursor::showCursor(bool a) noexcept
        {
            isVisible = a;
            mom->getDevice()->ShowMouse(a);
        }

        void cursor::showTexture(bool a) noexcept
        {
            isRender = a;
            mom->getDevice()->ShowMouse(!a);
        }

        bool cursor::manage(device::input *a) noexcept
        {
            if(pos == a->mouse_pos)
                return false;

            pos = a->mouse_pos;
            return true;
        }

        bool cursor::cursorIsShow() const noexcept
        {
            return isVisible;
        }

        bool cursor::textureIsShow() const noexcept
        {
            return isRender;
        }

        math::vec2i cursor::getPosition() const noexcept
        {
            return pos;
        }

        std::shared_ptr<driver::texture> cursor::getTexture() const noexcept
        {
            return tex;
        }

        std::shared_ptr<driver::material> cursor::getMaterial() const noexcept
        {
            return rnd;
        }

        void cursor::render() noexcept
        {
            if(!mom || !isRender || !tex)
                return;

            mom->getDrawManager()->setActiveMaterial(mom->getTheme()->getAddMaterial());
            mom->getDrawManager()->drawTexture(tex.get(), pos);
        }
    }
}
