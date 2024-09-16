#ifndef CURSOR
#define CURSOR

#include "interface.h"

namespace sleek
{
    namespace gui
    {
        class Interface;
        class cursor : public std::enable_shared_from_this<cursor>
        {
            public:
                cursor(Interface*) noexcept;
                virtual ~cursor() noexcept;

                virtual INTERFACE_GUI_CODE getType() const noexcept { return IGT_CURSOR; }

                inline std::shared_ptr<cursor> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual void showCursor(bool) noexcept;
                virtual void showTexture(bool) noexcept;
                virtual bool manage(device::input*) noexcept;
                virtual void setTexture(std::shared_ptr<driver::texture>) noexcept;
                virtual void setPosition(const math::vec2i&) noexcept;

                virtual std::shared_ptr<driver::material> getMaterial() const noexcept;
                virtual std::shared_ptr<driver::texture> getTexture() const noexcept;

                virtual math::vec2i getPosition() const noexcept;
                virtual bool textureIsShow() const noexcept;
                virtual bool cursorIsShow() const noexcept;

                virtual void render() noexcept;
            protected:
                bool isRender, isVisible;
                std::shared_ptr<driver::material> rnd;
                std::shared_ptr<driver::texture> tex;
                Interface *mom;
            private:
                math::vec2i pos;
        };
    }
}
#endif // NODE
