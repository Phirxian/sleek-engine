#include "event.h"

namespace sleek
{
    namespace device
    {
        event::event() noexcept : asRunning(true)
        {
        }

        event::~event() noexcept
        {
        }

        void event::force(input a) noexcept
        {
            manage(&a);
        }

        bool event::manage(input *a) noexcept
        {
            current = a;
            if(a->exit_msg) exit();
            //a->clear();
            return false;
        }

        void event::reset() noexcept
        {
            current->clear();
        }

        void event::exit() noexcept
        {
            kill();
        }

        void event::kill() noexcept
        {
            asRunning = false;
        }

        /** ********************************************** **/

        input::input() noexcept
        {
            clear();
        }

        void input::operator = (const input &n) noexcept
        {
            type = n.type;
            for(u16 i = 0; i<MOUSE_CODE_COUNT; ++i)
                mouse[i] = n.mouse[i];
            for(u16 i = 0; i<KEY_KEY_CODES_COUNT; ++i)
                key[i] = n.key[i];

            gui.called = n.gui.called;
            gui.type = n.gui.type;
            gui.code = n.gui.code;

            exit_msg = n.exit_msg;
            mouse_pos = n.mouse_pos;
        }

        void input::clear() noexcept
        {
            type = EVENT_NOTHINK;
            
            for(u16 i = 0; i<MOUSE_CODE_COUNT; ++i)
                mouse[i] = false;
                
            for(u16 i = 0; i<KEY_KEY_CODES_COUNT; ++i)
                key[i] = false;

            gui.called = 0;
            gui.type = gui::IGT_NOTHINK;
            gui.code = gui::IET_NOTHINK;

            exit_msg = false;
        }
    }
}
