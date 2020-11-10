#ifndef __DEVICE_STUB_HEADER__
#define __DEVICE_STUB_HEADER__

#include "../math/timer.h"
#include "../math/math.h"
#include <string>

namespace sleek
{
    namespace device
    {
        struct Device_stub
        {
            Device_stub(bool fl = false) noexcept :
                decorator(true), fullscreen(fl),
                size(640, 480), bits(16),
                name("SleekThink")
            {
            }

            Device_stub(const math::vec2i sz, u8 b, bool fl = false) noexcept :
                decorator(true), fullscreen(fl),
                size(sz), bits(b),
                name("SleekThink")
            {
            }

            Device_stub(u32 w, u32 h, u8 b, bool fl = false) noexcept :
                decorator(true), fullscreen(fl),
                size(w, h), bits(b),
                name("SleekThink")
            {
            }

            ~Device_stub() noexcept
            {
            }

            u8 bits;
            bool fullscreen, decorator;
            math::vec2i size;
            std::string name;

            //! read only

            void *visual;
            void *fbconfig;
            void *display;
            void *window;
        };
    }
}

#endif // __DEVICE_STUB_HEADER__
