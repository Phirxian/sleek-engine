#ifndef TIMER
#define TIMER

#include "../define.h"
#include <chrono>

namespace sleek
{
    namespace math
    {
        class timer
        {
            public:
                timer() noexcept;
                ~timer() noexcept;

                void pause(bool) noexcept;

                void update() noexcept;
                void reset() noexcept;

                f32 getTimeMin() const noexcept  { return getTimeSec()/60;      }
                f32 getTimeSec() const noexcept  { return getTimeMsec()/1000.f; }
                f32 getTimeMsec() const noexcept { return timestamp;            }
            private:
                std::chrono::steady_clock::time_point timestart;
                std::chrono::steady_clock::time_point time;
                f32 timestamp;
        };
    }
}

#endif
