#ifndef DEVICE_WINDOW_MANAGER_SDL2
#define DEVICE_WINDOW_MANAGER_SDL2

    #include "../../define.h"
    #include "../../compile.h"

    #if defined sdl2_device_support

    #include "../device.h"

    typedef struct SDL_Window SDL_Window;
    typedef union SDL_Event SDL_Event;

    namespace sleek
    {
        namespace device
        {
            class Device_sdl2 : public Device
            {
                public:
                    Device_sdl2(const Device_stub&) noexcept;
                    virtual ~Device_sdl2() noexcept;

                    virtual const DeviceWindowManager getType() const { return DWM_SDL2; }

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
                    void keymap(const SDL_Event&, input*) noexcept;
                    SDL_Window *display;
            };
        }
    }

    #endif
#endif
