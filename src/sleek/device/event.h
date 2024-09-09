#ifndef EVENT_RECEIVER
#define EVENT_RECEIVER

#include "../gui/type.h"
#include "keycode.h"

#include "../math/math.h"
#include <vector>

namespace sleek
{
    namespace gui
    {
        class frame;
        enum INTERFACE_EVENT_CODE;
        enum INTERFACE_GUI_CODE;
    }

    namespace device
    {
        struct input;
        class event
        {
            public:
                event() noexcept;
                ~event() noexcept;

                virtual void force(input*) noexcept;
                virtual bool manage(input*) noexcept;
                virtual void exit() noexcept;
            protected:
                void kill() noexcept;
                void reset() noexcept;
                input *current;
            private:
                friend class Device;
                friend class Device_sdl;
                friend class Device_sdl2;
                friend class Device_win;
                friend class Device_x11;
                friend class Device_xf86;
                friend class Device_glfw3;
                bool asRunning;
        };
        struct input
        {
            input() noexcept;
            void operator = (const input&) noexcept;
            void clear() noexcept;

            bool exit_msg;
            EVENTCODE type;

            bool mouse[MOUSE_CODE_COUNT];
            bool key[KEY_KEY_CODES_COUNT];
            bool key_state[KEY_KEY_CODES_COUNT];

            struct
            {
                class gui::frame *called;
                gui::INTERFACE_GUI_CODE type;
                gui::INTERFACE_EVENT_CODE code;
            } gui;

            math::vec2i mouse_pos;
        };
    }
}
#endif // EVENTRECEIVER_H
