#ifndef DEVICE_WINDOW_MANAGER_X11
#define DEVICE_WINDOW_MANAGER_X11

    #include "../device.h"
    #include "../../define.h"
    #if defined x11_device_support

    #include <stdio.h>
    #include <stdlib.h>
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
    #include <X11/Xatom.h>
    #include <X11/keysym.h>
    #include <GL/glx.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/utsname.h>

    namespace sleek
    {
        namespace device
        {
            class Device_x11 : public Device
            {
                public:
                    Device_x11(const Device_stub&) noexcept;
                    virtual ~Device_x11() noexcept;

                    virtual const DeviceWindowManager getType() const { return DWM_X11; }

                    virtual bool run() noexcept;
                    virtual void begin() noexcept;
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
                    Window      window;
                    Display     *display;
                    XVisualInfo *vi;
                    GLXFBConfig *fb;
                    XSetWindowAttributes swa;
                private:
                    Cursor invisCursor;
                    void CreateX11Cursor() noexcept;
                    void keymap(XEvent,input*) noexcept;
            };
        }
    }

    #endif
#endif
