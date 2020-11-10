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
    }
}
