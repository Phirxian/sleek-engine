#include "sdl.h"
#if defined sdl_device_support

#if defined __linux
    #include <X11/Xlib.h>
#endif

#ifdef __linux
#define SDL_VIDEO_DRIVER_X11
#endif

extern "C" {
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_video.h>
    #include <SDL2/SDL_syswm.h>
}

namespace sleek
{
    namespace device
    {
        Device_sdl::Device_sdl(const Device_stub &a) noexcept : Device(a)
        {
            display = 0;
            SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK);
            atexit(SDL_Quit);

            const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo();

            videoFlags  = SDL_OPENGL;
            videoFlags |= SDL_GL_DOUBLEBUFFER;
            videoFlags |= SDL_HWPALETTE;
            videoFlags |= SDL_RESIZABLE;

            if(videoInfo->hw_available) videoFlags |= SDL_HWSURFACE;
            else videoFlags |= SDL_SWSURFACE;

            if(videoInfo->blit_hw)
                videoFlags |= SDL_HWACCEL;

            /* Sets up OpenGL double buffering */
            SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

            display = SDL_SetVideoMode(a.size.x, a.size.y, a.bits, videoFlags);

            SDL_SysWMinfo wminfo;
            SDL_GetWMInfo(&wminfo);

            running = display != 0;

            if(!running)
            {
                std::cout << "Could not take device_sdl !!\n" << std::endl;
                return;
            }

            #ifdef __linux
                info.display = wminfo.info.x11.display;
                info.window = &wminfo.info.x11.window;
                info.visual = nullptr;
            #else
                info.display = nullptr;
                info.window = &wminfo.window;
                info.visual = nullptr;
            #endif

            welcomeMessage();
        }

        Device_sdl::~Device_sdl() noexcept
        {
            if(display != 0)
                SDL_FreeSurface(display);
            SDL_Quit();
        }

        void Device_sdl::setCaption(const std::string &name) noexcept
        {
            Device::setCaption(name);
            SDL_WM_SetCaption(name.c_str(), "sleek-think");
        }

        void Device_sdl::setVideoSize(const math::vec2i &i) noexcept
        {
            Device::setVideoSize(i);
            display = SDL_SetVideoMode(info.size.x, info.size.y, info.bits, videoFlags);
        }

        void Device_sdl::setWindowPos(const math::vec2i &i) noexcept
        {
            //SDL_SetWindowPosition(display, i.x, i.y);
        }

        void Device_sdl::enableWindowDecorator(bool z) noexcept
        {
            Device::enableWindowDecorator(z);
            videoFlags ^= z*SDL_NOFRAME;
            display = SDL_SetVideoMode(info.size.x, info.size.y, info.bits, videoFlags);
        }

        void Device_sdl::setGamma(const math::pixel &c) noexcept
        {
            SDL_SetGammaRamp((Uint16*)&c.red, (Uint16*)&c.green, (Uint16*)&c.blue);
        }

        void Device_sdl::setFullScreen(bool f) noexcept
        {
            info.fullscreen = f;
            videoFlags ^= SDL_FULLSCREEN;
            display = SDL_SetVideoMode(info.size.x, info.size.y, info.bits, videoFlags);
        }

        math::vec2i Device_sdl::getDesktopVideoSize() const noexcept
        {
            math::vec2i size;
            #ifndef __linux
                const SDL_VideoInfo *hw = SDL_GetVideoInfo();
                size.x = hw->current_w;
                size.y = hw->current_h;
            #else
                Display *display = XOpenDisplay(0);
                size.x = DefaultScreenOfDisplay(display)->width;
                size.y = DefaultScreenOfDisplay(display)->height;
                XCloseDisplay(display);
            #endif
            return size;
        }

        bool Device_sdl::run() noexcept
        {
            reading = true;
            SDL_Event sdl_event;

            SDL_PollEvent(&sdl_event);
            SDL_GetMouseState(&current->mouse_pos.x,&current->mouse_pos.y);

            if(sdl_event.type == SDL_QUIT)
                current->exit_msg = true;

            keymap(sdl_event, current);

            return Device::run();
        }

        void Device_sdl::begin(const math::pixel &color) noexcept
        {
            if(!reading) return;
            Device::begin();
        }

        bool Device_sdl::manage() noexcept
        {
            evt->manage(current);
            current->clear();
            running = evt->asRunning;
            return true;
        }

        void Device_sdl::end() noexcept
        {
            SDL_GL_SwapBuffers();
            if(!reading) return;
            Device::end();
            os::Sleeping(1);
            reading = false;
        }

        void Device_sdl::WarpMouse(const math::vec2i &i) noexcept
        {
            SDL_WarpMouse(i.x, i.y);
        }

        void Device_sdl::ShowMouse(bool i) noexcept
        {
            SDL_ShowCursor(i);
        }

        void Device_sdl::keymap(const SDL_Event &a, input *i) noexcept
        {
            /** event type **/
            if(a.type == SDL_KEYDOWN) i->type = EVENT_KEY_DOWN;
            else if(a.type == SDL_KEYUP) i->type = EVENT_KEY_UP;
            else if(a.type == SDL_MOUSEBUTTONDOWN) i->type = EVENT_MOUSSE_DOWN;
            else if(a.type == SDL_MOUSEBUTTONUP) i->type = EVENT_MOUSSE_UP;
            else if(a.type == SDL_VIDEORESIZE)
            {
                setVideoSize({a.resize.w, a.resize.h});
                i->type = EVENT_WINDOW_RESIZE;
            }
            else if(a.type == SDL_MOUSEMOTION) i->type = EVENT_MOUSSE_MOVED;
            else i->type = EVENT_NOTHINK;
            /** mouse event **/
            if(a.button.button == SDL_BUTTON_LEFT) { i->mouse[MOUSE_LEFT] = true; i->key[KEY_LBUTTON] = true; }
            if(a.button.button == SDL_BUTTON_MIDDLE) { i->mouse[MOUSE_MIDDLE] = true; i->key[KEY_MBUTTON] = true; }
            if(a.button.button == SDL_BUTTON_RIGHT) { i->mouse[MOUSE_RIGHT] = true; i->key[KEY_RBUTTON] = true; }
            /** key event **/
//                if(a.key.keysym.sym == SDLK_C) i->key[KEY_CANCEL] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_XBUTTON1] = true;
//                if(a.key.keysym.sym == SDLK_X) i->key[KEY_XBUTTON2] = true;
//                if(a.key.keysym.sym == SDLK_B) i->key[KEY_BACK] = true;
            if(a.key.keysym.sym == SDLK_TAB) i->key[KEY_TAB] = true;
            if(a.key.keysym.sym == SDLK_CLEAR) i->key[KEY_CLEAR] = true;
            if(a.key.keysym.sym == SDLK_RETURN) i->key[KEY_RETURN] = true;
            if(a.key.keysym.sym == SDLK_RSHIFT || a.key.keysym.sym == SDLK_LSHIFT) i->key[KEY_SHIFT] = true;
            if(a.key.keysym.sym == SDLK_RCTRL || a.key.keysym.sym == SDLK_LCTRL) i->key[KEY_CONTROL] = true;
            if(a.key.keysym.sym == SDLK_MENU) i->key[KEY_MENU] = true;
            if(a.key.keysym.sym == SDLK_PAUSE) i->key[KEY_PAUSE] = true;
//                if(a.key.keysym.sym == SDLK_C) i->key[KEY_CAPITAL] = true;
//                if(a.key.keysym.sym == SDLK_K) i->key[KEY_KANA] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_HANGUEL] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_HANGUL] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_JUNJA] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_FINAL] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_HANJA] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_KANJI] = true;
            if(a.key.keysym.sym == SDLK_ESCAPE) i->key[KEY_ESCAPE] = true;
//                if(a.key.keysym.sym == SDLK_C) i->key[KEY_CONVERT] = true;
//                if(a.key.keysym.sym == SDLK_N) i->key[KEY_NONCONVERT] = true;
//                if(a.key.keysym.sym == SDLK_A) i->key[KEY_ACCEPT] = true;
            if(a.key.keysym.sym == SDLK_MODE) i->key[KEY_MODECHANGE] = true;
            if(a.key.keysym.sym == SDLK_SPACE) i->key[KEY_SPACE] = true;
//                if(a.key.keysym.sym == SDLK_P) i->key[KEY_PRIOR] = true;
//                if(a.key.keysym.sym == SDLK_N) i->key[KEY_NEXT] = true;
            if(a.key.keysym.sym == SDLK_END) i->key[KEY_END] = true;
            if(a.key.keysym.sym == SDLK_HOME) i->key[KEY_HOME] = true;
            if(a.key.keysym.sym == SDLK_LEFT) i->key[KEY_LEFT] = true;
            if(a.key.keysym.sym == SDLK_UP) i->key[KEY_UP] = true;
            if(a.key.keysym.sym == SDLK_RIGHT) i->key[KEY_RIGHT] = true;
            if(a.key.keysym.sym == SDLK_DOWN) i->key[KEY_DOWN] = true;
//                if(a.key.keysym.sym == SDLK_S) i->key[KEY_SELECT] = true;
//            if(a.key.keysym.sym == SDLK_PRINT) i->key[KEY_PRINT] = true;
//                if(a.key.keysym.sym == SDLK_E) i->key[KEY_EXECUT] = true;
//                if(a.key.keysym.sym == SDLK_S) i->key[KEY_SNAPSHOT] = true;
            if(a.key.keysym.sym == SDLK_INSERT) i->key[KEY_INSERT] = true;
            if(a.key.keysym.sym == SDLK_DELETE) i->key[KEY_DELETE] = true;
            if(a.key.keysym.sym == SDLK_HELP) i->key[KEY_HELP] = true;
            if(a.key.keysym.sym == SDLK_0) i->key[KEY_KEY_0] = true;
            if(a.key.keysym.sym == SDLK_1) i->key[KEY_KEY_1] = true;
            if(a.key.keysym.sym == SDLK_2) i->key[KEY_KEY_2] = true;
            if(a.key.keysym.sym == SDLK_3) i->key[KEY_KEY_3] = true;
            if(a.key.keysym.sym == SDLK_4) i->key[KEY_KEY_4] = true;
            if(a.key.keysym.sym == SDLK_5) i->key[KEY_KEY_5] = true;
            if(a.key.keysym.sym == SDLK_6) i->key[KEY_KEY_6] = true;
            if(a.key.keysym.sym == SDLK_7) i->key[KEY_KEY_7] = true;
            if(a.key.keysym.sym == SDLK_8) i->key[KEY_KEY_8] = true;
            if(a.key.keysym.sym == SDLK_9) i->key[KEY_KEY_9] = true;
            if(a.key.keysym.sym == SDLK_a) i->key[KEY_KEY_A] = true;
            if(a.key.keysym.sym == SDLK_b) i->key[KEY_KEY_B] = true;
            if(a.key.keysym.sym == SDLK_c) i->key[KEY_KEY_C] = true;
            if(a.key.keysym.sym == SDLK_d) i->key[KEY_KEY_D] = true;
            if(a.key.keysym.sym == SDLK_e) i->key[KEY_KEY_E] = true;
            if(a.key.keysym.sym == SDLK_f) i->key[KEY_KEY_F] = true;
            if(a.key.keysym.sym == SDLK_g) i->key[KEY_KEY_G] = true;
            if(a.key.keysym.sym == SDLK_h) i->key[KEY_KEY_H] = true;
            if(a.key.keysym.sym == SDLK_i) i->key[KEY_KEY_I] = true;
            if(a.key.keysym.sym == SDLK_j) i->key[KEY_KEY_J] = true;
            if(a.key.keysym.sym == SDLK_k) i->key[KEY_KEY_K] = true;
            if(a.key.keysym.sym == SDLK_l) i->key[KEY_KEY_L] = true;
            if(a.key.keysym.sym == SDLK_m) i->key[KEY_KEY_M] = true;
            if(a.key.keysym.sym == SDLK_n) i->key[KEY_KEY_N] = true;
            if(a.key.keysym.sym == SDLK_o) i->key[KEY_KEY_O] = true;
            if(a.key.keysym.sym == SDLK_p) i->key[KEY_KEY_P] = true;
            if(a.key.keysym.sym == SDLK_q) i->key[KEY_KEY_Q] = true;
            if(a.key.keysym.sym == SDLK_r) i->key[KEY_KEY_R] = true;
            if(a.key.keysym.sym == SDLK_s) i->key[KEY_KEY_S] = true;
            if(a.key.keysym.sym == SDLK_t) i->key[KEY_KEY_T] = true;
            if(a.key.keysym.sym == SDLK_u) i->key[KEY_KEY_U] = true;
            if(a.key.keysym.sym == SDLK_v) i->key[KEY_KEY_V] = true;
            if(a.key.keysym.sym == SDLK_w) i->key[KEY_KEY_W] = true;
            if(a.key.keysym.sym == SDLK_x) i->key[KEY_KEY_X] = true;
            if(a.key.keysym.sym == SDLK_y) i->key[KEY_KEY_Y] = true;
            if(a.key.keysym.sym == SDLK_z) i->key[KEY_KEY_Z] = true;
//            if(a.key.keysym.sym == SDLK_LMETA) i->key[KEY_LWIN] = true;
//            if(a.key.keysym.sym == SDLK_RMETA) i->key[KEY_RWIN] = true;
//                if(a.key.keysym.sym == SDLK_A) i->key[KEY_APPS] = true;
//                if(a.key.keysym.sym == SDLK_S) i->key[KEY_SLEEP] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_NUMPAD0] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_NUMPAD1] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_NUMPAD2] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_NUMPAD3] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_NUMPAD4] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_NUMPAD5] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_NUMPAD6] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_NUMPAD7] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_NUMPAD8] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_NUMPAD9] = true;
            if(a.key.keysym.sym == SDLK_ASTERISK) i->key[KEY_MULTIPLY] = true;
//                if(a.key.keysym.sym == SDLK_) i->key[KEY_ADD] = true;
//                if(a.key.keysym.sym == SDLK_s) i->key[KEY_SEPARATOR] = true;
            if(a.key.keysym.sym == SDLK_MINUS) i->key[KEY_SUBTRACT] = true;
//                if(a.key.keysym.sym == SDLK_D) i->key[KEY_DECIMAL] = true;
            if(a.key.keysym.sym == SDLK_SLASH) i->key[KEY_DIVIDE] = true;
            if(a.key.keysym.sym == SDLK_F1) i->key[KEY_F1] = true;
            if(a.key.keysym.sym == SDLK_F2) i->key[KEY_F2] = true;
            if(a.key.keysym.sym == SDLK_F3) i->key[KEY_F3] = true;
            if(a.key.keysym.sym == SDLK_F4) i->key[KEY_F4] = true;
            if(a.key.keysym.sym == SDLK_F5) i->key[KEY_F5] = true;
            if(a.key.keysym.sym == SDLK_F6) i->key[KEY_F6] = true;
            if(a.key.keysym.sym == SDLK_F7) i->key[KEY_F7] = true;
            if(a.key.keysym.sym == SDLK_F8) i->key[KEY_F8] = true;
            if(a.key.keysym.sym == SDLK_F9) i->key[KEY_F9] = true;
            if(a.key.keysym.sym == SDLK_F10) i->key[KEY_F10] = true;
            if(a.key.keysym.sym == SDLK_F11) i->key[KEY_F11] = true;
            if(a.key.keysym.sym == SDLK_F12) i->key[KEY_F12] = true;
            if(a.key.keysym.sym == SDLK_F13) i->key[KEY_F13] = true;
            if(a.key.keysym.sym == SDLK_F14) i->key[KEY_F14] = true;
            if(a.key.keysym.sym == SDLK_F15) i->key[KEY_F15] = true;
//            if(a.key.keysym.sym == SDLK_NUMLOCK) i->key[KEY_NUMLOCK] = true;
//            if(a.key.keysym.sym == SDLK_SCROLLOCK) i->key[KEY_SCROLL] = true;
            if(a.key.keysym.sym == SDLK_LSHIFT) i->key[KEY_LSHIFT] = true;
            if(a.key.keysym.sym == SDLK_RSHIFT) i->key[KEY_RSHIFT] = true;
            if(a.key.keysym.sym == SDLK_LCTRL) i->key[KEY_LCONTROL] = true;
            if(a.key.keysym.sym == SDLK_RCTRL) i->key[KEY_RCONTROL] = true;
//            if(a.key.keysym.sym == SDLK_LMETA) i->key[KEY_LMENU] = true;
//            if(a.key.keysym.sym == SDLK_RMETA) i->key[KEY_RMENU] = true;
            if(a.key.keysym.sym == SDLK_PLUS) i->key[KEY_PLUS] = true;
            if(a.key.keysym.sym == SDLK_COMMA) i->key[KEY_COMMA] = true;
            if(a.key.keysym.sym == SDLK_MINUS) i->key[KEY_MINUS] = true;
            if(a.key.keysym.sym == SDLK_PERIOD) i->key[KEY_PERIOD] = true;
            if(a.key.keysym.sym == SDLK_AT) i->key[KEY_ATTN] = true;
//                if(a.key.keysym.sym == SDLK_c) i->key[KEY_CRSEL] = true;
//                if(a.key.keysym.sym == SDLK_E) i->key[KEY_EXSEL] = true;
//                if(a.key.keysym.sym == SDLK_E) i->key[KEY_EREOF] = true;
//                if(a.key.keysym.sym == SDLK_P) i->key[KEY_PLAY] = true;
//                if(a.key.keysym.sym == SDLK_Z) i->key[KEY_ZOOM] = true;
            if(a.key.keysym.sym == SDLK_PAGEUP) i->key[KEY_PA1] = true;
            if(a.key.keysym.sym == SDLK_CLEAR) i->key[KEY_OEM_CLEAR] = true;
        }
    }
}
#endif
