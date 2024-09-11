#ifndef COLOR_PICKER
#define COLOR_PICKER

#include "frame.h"

namespace sleek
{
    namespace gui
    {
        class interface;
        class scrollbar;
        class button;

        class colorpicker : public frame
        {
            public:
                colorpicker(interface*) noexcept;
                ~colorpicker() noexcept;

                virtual INTERFACE_GUI_CODE getType() const  noexcept { return IGT_COLORPICKER; }

                virtual void setScale(math::vec2i i) noexcept;

                virtual bool manage(device::input*) noexcept;

                virtual void setPickedColor(const math::pixel&) noexcept;
                virtual const math::pixel& getPickedColor() const noexcept;

                virtual void setBackgroundColor(const math::pixel&) noexcept;
                virtual const math::pixel& getBackgroundColor() const noexcept;

                virtual void render() noexcept;
            protected:
                bool isGradient, isColor, isInside;
                virtual void recalculatePickedColor() noexcept;
                virtual void createAlphaTexture() noexcept;
                virtual void createGradientTexture() noexcept;
                virtual void UpdateAbsolutePosition() noexcept;
            protected:
                std::shared_ptr<button> close;
                std::shared_ptr<scrollbar> scroll;
                std::shared_ptr<driver::texture> img[2];
            protected:
                math::pixel pickcolor, color;
                math::pixel background, white, black, alpha;
                math::aabbox2di colorbox, pickbox, gradient;
                math::vec2i pickpos;
                int colorpos;
        };
    }
}

#endif
