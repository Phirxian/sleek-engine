#include "../device/device.h"
#include "driver.h"

namespace sleek
{
    namespace driver
    {
        driver::driver(std::shared_ptr<device::Device> dev, std::shared_ptr<context> c) noexcept
            : src(dev), ctx(c), mat(std::make_shared<material>())
        {
        }

        driver::~driver() noexcept
        {
        }

        std::shared_ptr<context> driver::getContext()
        {
            return ctx;
        }

        void driver::pushScissor(math::aabbox2di box)
        {
            scissor.push_back(box);
        }

        math::aabbox2di driver::popScissor()
        {
            if (scissor.size())
            {
                auto last = scissor[scissor.size()-1];
                scissor.pop_back();
                return last;
            }

            return {0,0,0,0};
        }

        void driver::clearScissor()
        {
            scissor.clear();
        }
    }
}
