#ifndef DEVICE_WINDOW_MANAGER_SDL
#define DEVICE_WINDOW_MANAGER_SDL

    #include "../../define.h"
    #include "../../compile.h"

    #if defined sdl_device_support

    #include "../device.h"

    typedef struct SDL_Surface SDL_Surface;
    typedef union SDL_Event SDL_Event;

    namespace sleek
    {
        namespace device
        {
            class Device_sdl : public Device
            {
                public:
                    [[deprecated]]
                    Device_sdl(const Device_stub&) noexcept;
                    virtual ~Device_sdl() noexcept;

                    virtual const DeviceWindowManager getType() const { return DWM_SDL; }

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
                    int videoFlags;
                    void keymap(const SDL_Event&, input*) noexcept;
                    SDL_Surface *display;
            };
        }
    }

    #endif
#endif
