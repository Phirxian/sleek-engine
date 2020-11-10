#ifndef GUI_PICTURE
#define GUI_PICTURE

#include "frame.h"
#include "../driver/texture.h"

namespace sleek
{
    namespace gui
    {
        class picture : public frame
        {
            public:
                picture(interface*) noexcept;
                ~picture() noexcept;

                virtual INTERFACE_GUI_CODE getType() const noexcept { return IGT_PICTURE; }

                void setTexture(std::shared_ptr<driver::texture>) noexcept;
                std::shared_ptr<driver::texture> getTexture() const noexcept;

                virtual bool manage(device::input*) noexcept;

                virtual void render() noexcept;
            private:
                std::shared_ptr<driver::material> rnd;
                std::shared_ptr<driver::texture> pic;
                bool isHovored;
        };
    }
}

#endif

