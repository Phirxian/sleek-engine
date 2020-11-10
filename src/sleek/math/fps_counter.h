#include "timer.h"

namespace sleek
{
    namespace math
    {
        class fps_counter
        {
            public:
                fps_counter() :
                    localfps(-1), fps(0),
                    current(0), sum(0.f), avg(0.f)
                {
                    clock.update();
                    clock.reset();
                }

                inline void update()
                {
                    // calculate frame time
                    u32 last  = clock.getTimeMsec();
                    clock.update();

                    // last frame time
                    current = clock.getTimeMsec() - last;
                    // sum of frame time
                    sum += current;

                    ++localfps;

                    if(clock.getTimeMsec() >= 1000)
                    {
                        fps = localfps;
                        avg = sum/fps;

                        sum = 0.f;
                        localfps = 0;

                        clock.reset();
                    }
                }

                inline u32 getCurrentTime() const noexcept
                {
                    return current;
                }

                inline float getAvarageTime() const noexcept
                {
                    return avg;
                }

                inline u32 getFps() const noexcept
                {
                    return fps;
                }

            private:
                timer clock;
                float sum, avg;
                u32 localfps, fps;
                u32 current;
        };
    }
}
