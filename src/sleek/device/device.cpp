#include "device.h"
#include "common/sdl.h"
#include "common/sdl2.h"
#include "common/win.h"
#include "common/x11.h"
#include "common/xf86.h"
#include "common/glfw3.h"
#include <iostream>

namespace sleek
{
    namespace device
    {
        std::shared_ptr<Device> CreateDeviceWindowManager(const DeviceWindowManager &type, const Device_stub &info) noexcept
        {
            switch(type)
            {
                case DWM_AUTO:
                    // priority to plateform specific backend
                    #if defined x11_device_support
                        return std::make_shared<Device_x11>(info);
                    #elif defined win_device_support
                        return new Device_win(info));
                    #elif DWM_GLFW3
                        return new Device_glfw3(info));
                    #elif sdl2_device_support
                        return new Device_sdl2(info));
                    #elif sdl_device_support
                        return new Device_sdl(info));
                    #endif
                break;
                #if defined sdl_device_support
                    case DWM_SDL: return std::make_shared<Device_sdl>(info); break;
                #endif
                #if defined sdl2_device_support
                    case DWM_SDL2: return std::make_shared<Device_sdl2>(info); break;
                #endif
                #if defined x11_device_support
                    case DWM_X11: return std::make_shared<Device_x11>(info); break;
                #endif
                #if defined xf86_device_support
                    case DWM_XF86: return std::make_shared<Device_xf86>(info); break;
                #endif
                #if defined win_device_support
                    case DWM_WIN: return std::make_shared<Device_win>(info); break;
                #endif
                #if defined glfw3_device_support
                    case DWM_GLFW3: return std::make_shared<Device_glfw3>(info); break;
                #endif
            }

            return nullptr;
        }

        Device::Device(const Device_stub &a) noexcept :
            reading(true), current(new input()), ext(new event()),
            info(a), tm(new math::timer())
        {
            //log = spdlog::stdout_logger_mt("sleek-think");
            evt = ext;
            kbd = detectKeyboardLayout();
            printKeyboardLayout(kbd);
        }

        Device::~Device() noexcept
        {
            exit();
        }

        void Device::welcomeMessage() noexcept
        {
            printf("=========================================================================\n");
            printf("\t\t\t\tSleekThink %s\n", version);
            printf("=========================================================================\n");

            printf("backend: %s\n", DeviceWindowManagerName[getType()]);

            #if defined __linux
                std::string linuxversion;
                struct utsname LinuxInfo; uname(&LinuxInfo);
                linuxversion += LinuxInfo.sysname; linuxversion += " "; linuxversion += LinuxInfo.machine;
                linuxversion += "  Kernel "; linuxversion += LinuxInfo.release;
                linuxversion += LinuxInfo.version;
                std::cout << linuxversion << std::endl;
            #elif defined WIN32 || defined WIN64
            #endif

            cpu = std::make_shared<tool::cpuid>();
            cpu->detectVirtualProcessor();
            cpu->printQuickDescription();
        }

        std::shared_ptr<spdlog::logger> Device::getLogger() const noexcept
        {
            return nullptr;
        }

        std::shared_ptr<tool::cpuid> Device::getCPUID() const noexcept
        {
            return cpu;
        }

        void Device::setCaption(const std::string &name) noexcept
        {
            info.name = name;
        }

        const math::fps_counter& Device::getFpsCounter() const noexcept
        {
            return fps;
        }

        void Device::enableWindowDecorator(bool z) noexcept
        {
            info.decorator = z;
        }

        bool Device::run() noexcept
        {
            return running;
        }

        input* Device::getCurrentEvent() const noexcept
        {
            return current;
        }

        void Device::setEventReceiver(event *a) noexcept
        {
            if(a) evt = a;
            else evt = ext;
        }

        void Device::setVideoSize(const math::vec2i &i) noexcept
        {
            info.size = i;
            current->type = EVENT_WINDOW_RESIZE;
        }

        void Device::setFullScreen(bool f) noexcept
        {
            info.fullscreen = f;
        }

        event *Device::getEventReceiver() const noexcept
        {
            return evt;
        }

        void Device::begin() noexcept
        {
            tm->update();
            fps.update();
        }

        bool Device::manage() noexcept
        {
            return false;
        }

        bool Device::ready() const noexcept
        {
            return reading;
        }

        void Device::end() noexcept
        {
        }

        void Device::exit() noexcept
        {
            reading = false;
            running = false;
        }
    }
}
