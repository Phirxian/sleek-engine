#ifndef DEVICE
#define DEVICE

#include "icone.h"
#include "device_stub.h"
#include "../define.h"
#include "../driver/texture.h"
#include "../math/fps_counter.h"
#include "tool/cpuid.h"
#include "event.h"
#include <memory>

namespace spdlog
{
    class logger;
}

namespace sleek
{
    namespace device
    {
        enum DeviceWindowManager
        {
            DWM_AUTO,
            DWM_SDL,
            DWM_X11,
            DWM_XF86,
            DWM_GLFW3,
            DWM_WIN,
            DWM_COUNT
        };

        static const char* DeviceWindowManagerName[] = {
            "DWM_AUTO",
            "DWM_SDL",
            "DWM_X11",
            "DWM_XF86",
            "DWM_GLFW3",
            "DWM_WIN",
        };

        class Device : public std::enable_shared_from_this<Device>
        {
            public:
                Device(const Device_stub&) noexcept;
                virtual ~Device() noexcept;

                virtual const DeviceWindowManager getType() const { return DWM_COUNT; }

                virtual void setGamma(const math::pixel&) noexcept = 0;
                virtual void setCaption(const std::string&) noexcept;
                virtual void setEventReceiver(event*) noexcept;
                virtual void setVideoSize(const math::vec2i&) noexcept;
                virtual void setWindowPos(const math::vec2i&) noexcept = 0;
                virtual void setFullScreen(bool) noexcept;

                virtual void enableWindowDecorator(bool) noexcept;

                virtual math::vec2i getDesktopVideoSize() const noexcept = 0;

                virtual std::shared_ptr<tool::cpuid> getCPUID() const noexcept;
                virtual std::shared_ptr<spdlog::logger> getLogger() const noexcept;
                virtual const math::fps_counter& getFpsCounter() const noexcept;

                virtual event* getEventReceiver() const noexcept;
                virtual input* getCurrentEvent() const noexcept;

                inline Device_stub getInfo() const noexcept
                {
                    return info;
                }

                inline std::shared_ptr<Device> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual void WarpMouse(const math::vec2i&) noexcept = 0;
                virtual void ShowMouse(bool) noexcept = 0;

                virtual bool run() noexcept;
                virtual void exit() noexcept;
                virtual bool ready() const noexcept;
                virtual bool manage() noexcept;

                virtual void begin() noexcept;
                virtual void end() noexcept;
            protected:
                std::shared_ptr<spdlog::logger> log;
                std::shared_ptr<tool::cpuid> cpu;

                math::fps_counter fps;
                event *evt, *ext;
                Device_stub info;
                math::timer *tm;
                input* current;

                bool running, reading;

                void welcomeMessage() noexcept;
        };
        std::shared_ptr<Device> CreateDeviceWindowManager(const DeviceWindowManager&, const Device_stub&) noexcept;
    }
}

#endif
