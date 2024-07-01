#ifndef DEVICE_WINDOW_MANAGER_GLFW3
#define DEVICE_WINDOW_MANAGER_GLFW3

    #include "../../define.h"
    #include "../../compile.h"

    #if defined glfw3_device_support

    #include "../device.h"
    #define GLFW_INCLUDE_NONE
    #include <GLFW/glfw3.h>

    namespace sleek
    {
        namespace device
        {
            class Device_glfw3 : public Device
            {
                public:
                    Device_glfw3(const Device_stub&) noexcept;
                    virtual ~Device_glfw3() noexcept;

                    virtual const DeviceWindowManager getType() const { return DWM_GLFW3; }

                    virtual bool run() noexcept;
                    virtual void begin(const math::pixel&) noexcept;
                    virtual bool manage() noexcept;
                    virtual void end() noexcept;

                    virtual void setGamma(const math::pixel&) noexcept;
                    virtual void setCaption(const std::string&) noexcept;
                    virtual void setVideoSize(const math::vec2i&) noexcept;
                    virtual void setWindowPos(const math::vec2i&) noexcept;
                    virtual void setFullScreen(bool) noexcept;

                    virtual void enableWindowDecorator(bool) noexcept;
                    virtual math::vec2i getDesktopVideoSize() const noexcept;

                    virtual void WarpMouse(const math::vec2i&) noexcept;
                    virtual void ShowMouse(bool) noexcept;
                protected:
                    GLFWwindow *window;
                    GLFWmonitor *monitor;
            };
        }
    }

    #endif
#endif
