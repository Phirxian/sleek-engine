#ifndef DEVICE_WINDOW_MANAGER_XF86
#define DEVICE_WINDOW_MANAGER_XF86

    #include "../device.h"
    #include "../../define.h"
    #if defined xf86_device_support

    #include <stdio.h>
    #include <stdlib.h>
    #include <GL/glx.h>
    #include <X11/Xos.h>
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xatom.h>
    #include <X11/keysym.h>
    #include <sys/utsname.h>
    #include <X11/extensions/xf86vmode.h>

    namespace sleek
    {
        namespace device
        {
            class Device_xf86 : public Device
            {
                public:
                    Device_xf86(const Device_stub&);
                    virtual ~Device_xf86();

                    virtual void begin(const math::pixel&);
                    virtual bool manage();
                    virtual void end();

                    virtual void setGamma(const math::pixel&);
                    virtual void setCaption(const std::string&);
                    virtual void setVideoSize(const math::vector2di&);
                    virtual void setFullScreen(bool);

                    virtual void enableWindowDecorator(bool);
                protected:
                    Device_xf86(){}
                    Window      window;
                    Display     *display;
                    XVisualInfo *vi;
                    XEvent       xev;
                    XSetWindowAttributes swa;
                private:
                    void keymap(XEvent a, input *i, bool);
            };
        }
    }

    #endif
#endif
