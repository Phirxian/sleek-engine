#ifndef SPLASH
#define SPLASH

#include "device.h"
#include <functional>

namespace sleek
{
    namespace gui
    {
        class Interface;
    }
    namespace driver
    {
        class context;
        class driver;
    }
    namespace device
    {
        class Device;
        class Splash : public event, public std::enable_shared_from_this<Splash>
        {
            public:
                Splash(const DeviceWindowManager &info = DWM_AUTO, const math::vec2i &size = math::vec2i(200,50), bool window_decorator = false) noexcept;
                ~Splash() noexcept;

                inline std::shared_ptr<Splash> getptr() noexcept
                {
                    return shared_from_this();
                }

                bool manage(sleek::device::input *a) noexcept;

                void setCloseFunction(const std::function<bool()>) noexcept;

                void setPicture(std::shared_ptr<driver::texture>) noexcept;
                std::shared_ptr<driver::texture> getPicture() const noexcept;

                void resizeFromPicture() noexcept;
                void resize(const math::vec2i&) noexcept;

                driver::context* getRenderer() const noexcept;
                gui::Interface*  getGUIEnvirnoment() const noexcept;
                math::timer*     getTimer() const noexcept;

                void render() noexcept;
            protected:
                bool wait;
                std::function<bool()> close;
            protected:
                std::shared_ptr<Device>          screen;
                std::shared_ptr<driver::texture> csp;
                std::shared_ptr<driver::driver>  driver;
                std::shared_ptr<driver::context> renderer;
                std::shared_ptr<gui::Interface>  guienv;
                math::timer *tm;
        };
    }
}

#endif
