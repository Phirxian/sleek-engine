#ifndef GUI_PROGRESSBAR
#define GUI_PROGRESSBAR

#include "frame.h"

namespace sleek
{
    namespace gui
    {
        class progressbar : public frame
        {
            public:
                progressbar(interface*) noexcept;
                ~progressbar() noexcept;

                virtual INTERFACE_GUI_CODE getType() const  noexcept { return IGT_PROGRESSBAR; }

                void setValue(const s32) noexcept;
                void setMinValue(const s32) noexcept;
                void setMaxValue(const s32) noexcept;
                void setPercentage(const f32) noexcept;

                f32 getPercentage() const noexcept;
                s32 getMinValue() const noexcept;
                s32 getMaxValue() const noexcept;
                s32 getValue() const noexcept;

                bool manage(device::input*) noexcept;

                void render() noexcept;
            private:
                s32 min, max;
                f32 per, lst;
                bool isHovored;
        };
    }
}

#endif
