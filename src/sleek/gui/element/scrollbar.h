#ifndef GUI_SCROLLBAR
#define GUI_SCROLLBAR

#include "frame.h"

namespace sleek
{
    namespace gui
    {
        class button;

        enum SCROLL_BAR_ORIANTATION
        {
            SBO_VERTICAL,
            SBO_HORIZONTAL,
            SBO_COUNT
        };

        class scrollbar : public frame
        {
            public:
                scrollbar(Interface*) noexcept;
                ~scrollbar() noexcept;

                virtual INTERFACE_GUI_CODE getType() const  noexcept { return IGT_SCROLLBAR; }

                virtual void setOrientation(SCROLL_BAR_ORIANTATION);
                virtual SCROLL_BAR_ORIANTATION getOrientation();

                virtual void setStep(const s32) noexcept;
                virtual void setValue(const s32) noexcept;
                virtual void setMin(const s32) noexcept;
                virtual void setMax(const s32) noexcept;
                virtual void setPercentage(const f32) noexcept;

                virtual f32 getPercentage() const noexcept;
                virtual s32 getMin() const noexcept;
                virtual s32 getMax() const noexcept;
                virtual s32 getValue() const noexcept;
                virtual s32 getStep() const noexcept;

                virtual bool manage(device::input*) noexcept;

                virtual void render() noexcept;

            protected:
                virtual void UpdateChildPosition() noexcept;

            private:
                std::shared_ptr<button> add;
                std::shared_ptr<button> sub;
                s32 min, max, step;
                f32 per;
                SCROLL_BAR_ORIANTATION orient;
                bool isHovored, isLeftDown;
        };
    }
}

#endif
