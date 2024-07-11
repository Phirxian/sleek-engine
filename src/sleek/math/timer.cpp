#include "timer.h"

#include <sys/time.h>
#include <unistd.h>
#include <chrono>

namespace sleek
{
    namespace math
    {
        timer::timer() noexcept
        {
            timestart = time = std::chrono::steady_clock::now();
            timestamp = 0;
        }

        timer::~timer() noexcept
        {
        }

        void timer::pause(bool i) noexcept
        {
            time = std::chrono::steady_clock::now();
            timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(time - timestart).count() * 1e-6;
        }

        void timer::update() noexcept
        {
            time = std::chrono::steady_clock::now();
            timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(time - timestart).count() * 1e-6;
        }

        void timer::reset() noexcept
        {
            timestart = time = std::chrono::steady_clock::now();
            timestamp = 0;
        }
    }
}
