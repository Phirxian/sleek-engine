#ifndef DEVICE_WINDOW_MANAGER_WIN
#define DEVICE_WINDOW_MANAGER_WIN

    #include "../device.h"
    #include "../../define.h"
    #if defined win_device_support
    #include <windows.h>

    namespace sleek
    {
        namespace device
        {
            class Device_win : public Device
            {
                public:
                    Device_win(const Device_stub&);
                    virtual ~Device_win();

                    virtual const DeviceWindowManager getType() const { return DWM_WIN; }

                    virtual void begin();
                    virtual bool manage();
                    virtual bool run();
                    virtual void end();
                    virtual void exit();

                    virtual void enableWindowDecorator(bool);
                    virtual math::vec2i getDesktopVideoSize() const;
                    virtual void setWindowPos(const math::vec2i&);

                    virtual void setGamma(const math::pixel&);
                    virtual void setCaption(const std::string&);
                    virtual void setVideoSize(const math::vec2i&);
                    virtual void setFullScreen(bool);
                protected:
                    Device_win(){}
                    HWND screen;
                    HDC dc;
                    WNDCLASS wc;
                    PIXELFORMATDESCRIPTOR pfd;
            };
        }
    }

    #endif
#endif

