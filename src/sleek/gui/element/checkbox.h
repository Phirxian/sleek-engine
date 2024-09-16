#ifndef GUI_CHECKBOX
#define GUI_CHECKBOX

#include "frame.h"

namespace sleek
{
    namespace gui
    {
        class button;

        class checkbox : public frame
        {
            public:
                checkbox(Interface*) noexcept;
                ~checkbox() noexcept;

                virtual INTERFACE_GUI_CODE getType() const  noexcept { return IGT_CHECKBOX; }

                virtual void setChecked(const bool) noexcept;
                virtual f32 getChecked() const noexcept;

                virtual bool manage(device::input*) noexcept;

                virtual void UpdateChildPosition() noexcept;
                virtual void UpdateFontPos() noexcept;

                virtual void render() noexcept;

            private:
                std::shared_ptr<button> check;
                bool isChecked;
        };
    }
}

#endif
