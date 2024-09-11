#include "sdl2.h"
#if defined sdl2_device_support

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
        Device_sdl2::Device_sdl2(const Device_stub &a) noexcept : Device(a)
        {
            display = 0;
            SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK);
            atexit(SDL_Quit);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

            display = SDL_CreateWindow(
                a.name.c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                a.size.x, a.size.y,
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                a.fullscreen*SDL_WINDOW_FULLSCREEN
            );


            SDL_SysWMinfo wminfo;
            SDL_GetWindowWMInfo(display, &wminfo);

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

            SDL_GLContext glcontext = SDL_GL_CreateContext(display);
            welcomeMessage();
        }

        Device_sdl2::~Device_sdl2() noexcept
        {
            if(display != 0)
                SDL_DestroyWindow(display);
            SDL_Quit();
        }

        void Device_sdl2::setCaption(const std::string &name) noexcept
        {
            Device::setCaption(name);
            SDL_SetWindowTitle(display, name.c_str());
        }

        void Device_sdl2::setVideoSize(const math::vec2i &i) noexcept
        {
            Device::setVideoSize(i);
            SDL_SetWindowSize(display, info.size.x, info.size.y);
            //SDL_WM_SetIcon(IMG_ReadXPMFromArray((char**)Device_icone),0);
        }

        void Device_sdl2::setWindowPos(const math::vec2i &i) noexcept
        {
            SDL_SetWindowPosition(display, i.x, i.y);
        }

        void Device_sdl2::enableWindowDecorator(bool z) noexcept
        {
            Device::enableWindowDecorator(z);
            SDL_SetWindowFullscreen(display, z ? SDL_WINDOW_FULLSCREEN : 0);
        }

        void Device_sdl2::setGamma(const math::pixel &c) noexcept
        {
            SDL_SetWindowGammaRamp(display, (Uint16*)&c.red, (Uint16*)&c.green, (Uint16*)&c.blue);
        }

        void Device_sdl2::setFullScreen(bool f) noexcept
        {
            info.fullscreen = f;
            SDL_SetWindowBordered(display, SDL_bool(f));
        }

        math::vec2i Device_sdl2::getDesktopVideoSize() const noexcept
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

        bool Device_sdl2::run() noexcept
        {
            reading = true;
            SDL_Event sdl_event;

            while(SDL_PollEvent(&sdl_event))
            {
                SDL_GetMouseState(&current->mouse_pos.x, &current->mouse_pos.y);

                if(sdl_event.type == SDL_QUIT)
                    current->exit_msg = true;

                keymap(sdl_event, current);
            }

            return Device::run();
        }

        void Device_sdl2::begin(const math::pixel &color) noexcept
        {
            if(!reading) return;
            Device::begin();
        }

        bool Device_sdl2::manage() noexcept
        {
            evt->manage(current);
            current->clear();
            running = evt->asRunning;
            return true;
        }

        void Device_sdl2::end() noexcept
        {
            SDL_GL_SwapWindow(display);
            if(!reading) return;
            Device::end();
            reading = false;
        }

        void Device_sdl2::WarpMouse(const math::vec2i &i) noexcept
        {
            SDL_WarpMouseInWindow(display, i.x, i.y);
        }

        void Device_sdl2::ShowMouse(bool i) noexcept
        {
            SDL_ShowCursor(i);
        }

        void Device_sdl2::keymap(const SDL_Event &a, input *i) noexcept
        {
            bool val = false;
            
            /** event type **/
            if(a.type == SDL_KEYDOWN)
            {
                i->type = EVENT_KEY_DOWN;
                val = true;
            }
            else if(a.type == SDL_KEYUP)
            {
                i->type = EVENT_KEY_UP;
                val = false;
            }
            else if(a.type == SDL_MOUSEBUTTONDOWN)
            {
                i->type = EVENT_MOUSSE_DOWN;
                val = true;
            }
            else if(a.type == SDL_MOUSEBUTTONUP)
            {
                i->type = EVENT_MOUSSE_UP;
                val = false;
            }
            else if(a.type == SDL_MOUSEMOTION)
            {
                i->type = EVENT_MOUSSE_MOVED;
                val = false;
            }
            else if(a.type == SDL_WINDOWEVENT && a.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                if(a.window.data1 && a.window.data2)
                {
                    setVideoSize(math::vec2i{a.window.data1, a.window.data2});
                    i->type = EVENT_WINDOW_RESIZE;
                }
            }
            else
                i->type = EVENT_NOTHINK;

            /** mouse event **/
            if(a.button.button == SDL_BUTTON_LEFT) { i->mouse[MOUSE_LEFT] = true; val = true; i->setkey(KEY_LBUTTON, val); }
            if(a.button.button == SDL_BUTTON_MIDDLE) { i->mouse[MOUSE_MIDDLE] = true; val = true; i->setkey(KEY_MBUTTON, val); }
            if(a.button.button == SDL_BUTTON_RIGHT) { i->mouse[MOUSE_RIGHT] = true; val = true; i->setkey(KEY_RBUTTON, val); }
            /** key event **/
//                if(a.key.keysym.sym == SDLK_C) i->setkey(KEY_CANCEL, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_XBUTTON1, val);
//                if(a.key.keysym.sym == SDLK_X) i->setkey(KEY_XBUTTON2, val);
//                if(a.key.keysym.sym == SDLK_B) i->setkey(KEY_BACK, val);
            if(a.key.keysym.sym == SDLK_TAB) i->setkey(KEY_TAB, val);
            if(a.key.keysym.sym == SDLK_CLEAR) i->setkey(KEY_CLEAR, val);
            if(a.key.keysym.sym == SDLK_RETURN) i->setkey(KEY_RETURN, val);
            if(a.key.keysym.sym == SDLK_RSHIFT || a.key.keysym.sym == SDLK_LSHIFT) i->setkey(KEY_SHIFT, val);
            if(a.key.keysym.sym == SDLK_RCTRL || a.key.keysym.sym == SDLK_LCTRL) i->setkey(KEY_CONTROL, val);
            if(a.key.keysym.sym == SDLK_MENU) i->setkey(KEY_MENU, val);
            if(a.key.keysym.sym == SDLK_PAUSE) i->setkey(KEY_PAUSE, val);
//                if(a.key.keysym.sym == SDLK_C) i->setkey(KEY_CAPITAL, val);
//                if(a.key.keysym.sym == SDLK_K) i->setkey(KEY_KANA, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_HANGUEL, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_HANGUL, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_JUNJA, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_FINAL, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_HANJA, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_KANJI, val);
            if(a.key.keysym.sym == SDLK_ESCAPE) i->setkey(KEY_ESCAPE, val);
//                if(a.key.keysym.sym == SDLK_C) i->setkey(KEY_CONVERT, val);
//                if(a.key.keysym.sym == SDLK_N) i->setkey(KEY_NONCONVERT, val);
//                if(a.key.keysym.sym == SDLK_A) i->setkey(KEY_ACCEPT, val);
            if(a.key.keysym.sym == SDLK_MODE) i->setkey(KEY_MODECHANGE, val);
            if(a.key.keysym.sym == SDLK_SPACE) i->setkey(KEY_SPACE, val);
//                if(a.key.keysym.sym == SDLK_P) i->setkey(KEY_PRIOR, val);
//                if(a.key.keysym.sym == SDLK_N) i->setkey(KEY_NEXT, val);
            if(a.key.keysym.sym == SDLK_END) i->setkey(KEY_END, val);
            if(a.key.keysym.sym == SDLK_HOME) i->setkey(KEY_HOME, val);
            if(a.key.keysym.sym == SDLK_LEFT) i->setkey(KEY_LEFT, val);
            if(a.key.keysym.sym == SDLK_UP) i->setkey(KEY_UP, val);
            if(a.key.keysym.sym == SDLK_RIGHT) i->setkey(KEY_RIGHT, val);
            if(a.key.keysym.sym == SDLK_DOWN) i->setkey(KEY_DOWN, val);
//                if(a.key.keysym.sym == SDLK_S) i->setkey(KEY_SELECT, val);
//            if(a.key.keysym.sym == SDLK_PRINT) i->setkey(KEY_PRINT, val);
//                if(a.key.keysym.sym == SDLK_E) i->setkey(KEY_EXECUT, val);
//                if(a.key.keysym.sym == SDLK_S) i->setkey(KEY_SNAPSHOT, val);
            if(a.key.keysym.sym == SDLK_INSERT) i->setkey(KEY_INSERT, val);
            if(a.key.keysym.sym == SDLK_DELETE) i->setkey(KEY_DELETE, val);
            if(a.key.keysym.sym == SDLK_HELP) i->setkey(KEY_HELP, val);
            if(a.key.keysym.sym == SDLK_0) i->setkey(KEY_KEY_0, val);
            if(a.key.keysym.sym == SDLK_1) i->setkey(KEY_KEY_1, val);
            if(a.key.keysym.sym == SDLK_2) i->setkey(KEY_KEY_2, val);
            if(a.key.keysym.sym == SDLK_3) i->setkey(KEY_KEY_3, val);
            if(a.key.keysym.sym == SDLK_4) i->setkey(KEY_KEY_4, val);
            if(a.key.keysym.sym == SDLK_5) i->setkey(KEY_KEY_5, val);
            if(a.key.keysym.sym == SDLK_6) i->setkey(KEY_KEY_6, val);
            if(a.key.keysym.sym == SDLK_7) i->setkey(KEY_KEY_7, val);
            if(a.key.keysym.sym == SDLK_8) i->setkey(KEY_KEY_8, val);
            if(a.key.keysym.sym == SDLK_9) i->setkey(KEY_KEY_9, val);
            if(a.key.keysym.sym == SDLK_a) i->setkey(KEY_KEY_A, val);
            if(a.key.keysym.sym == SDLK_b) i->setkey(KEY_KEY_B, val);
            if(a.key.keysym.sym == SDLK_c) i->setkey(KEY_KEY_C, val);
            if(a.key.keysym.sym == SDLK_d) i->setkey(KEY_KEY_D, val);
            if(a.key.keysym.sym == SDLK_e) i->setkey(KEY_KEY_E, val);
            if(a.key.keysym.sym == SDLK_f) i->setkey(KEY_KEY_F, val);
            if(a.key.keysym.sym == SDLK_g) i->setkey(KEY_KEY_G, val);
            if(a.key.keysym.sym == SDLK_h) i->setkey(KEY_KEY_H, val);
            if(a.key.keysym.sym == SDLK_i) i->setkey(KEY_KEY_I, val);
            if(a.key.keysym.sym == SDLK_j) i->setkey(KEY_KEY_J, val);
            if(a.key.keysym.sym == SDLK_k) i->setkey(KEY_KEY_K, val);
            if(a.key.keysym.sym == SDLK_l) i->setkey(KEY_KEY_L, val);
            if(a.key.keysym.sym == SDLK_m) i->setkey(KEY_KEY_M, val);
            if(a.key.keysym.sym == SDLK_n) i->setkey(KEY_KEY_N, val);
            if(a.key.keysym.sym == SDLK_o) i->setkey(KEY_KEY_O, val);
            if(a.key.keysym.sym == SDLK_p) i->setkey(KEY_KEY_P, val);
            if(a.key.keysym.sym == SDLK_q) i->setkey(KEY_KEY_Q, val);
            if(a.key.keysym.sym == SDLK_r) i->setkey(KEY_KEY_R, val);
            if(a.key.keysym.sym == SDLK_s) i->setkey(KEY_KEY_S, val);
            if(a.key.keysym.sym == SDLK_t) i->setkey(KEY_KEY_T, val);
            if(a.key.keysym.sym == SDLK_u) i->setkey(KEY_KEY_U, val);
            if(a.key.keysym.sym == SDLK_v) i->setkey(KEY_KEY_V, val);
            if(a.key.keysym.sym == SDLK_w) i->setkey(KEY_KEY_W, val);
            if(a.key.keysym.sym == SDLK_x) i->setkey(KEY_KEY_X, val);
            if(a.key.keysym.sym == SDLK_y) i->setkey(KEY_KEY_Y, val);
            if(a.key.keysym.sym == SDLK_z) i->setkey(KEY_KEY_Z, val);
//            if(a.key.keysym.sym == SDLK_LMETA) i->setkey(KEY_LWIN, val);
//            if(a.key.keysym.sym == SDLK_RMETA) i->setkey(KEY_RWIN, val);
//                if(a.key.keysym.sym == SDLK_A) i->setkey(KEY_APPS, val);
//                if(a.key.keysym.sym == SDLK_S) i->setkey(KEY_SLEEP, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_NUMPAD0, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_NUMPAD1, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_NUMPAD2, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_NUMPAD3, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_NUMPAD4, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_NUMPAD5, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_NUMPAD6, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_NUMPAD7, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_NUMPAD8, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_NUMPAD9, val);
            if(a.key.keysym.sym == SDLK_ASTERISK) i->setkey(KEY_MULTIPLY, val);
//                if(a.key.keysym.sym == SDLK_) i->setkey(KEY_ADD, val);
//                if(a.key.keysym.sym == SDLK_s) i->setkey(KEY_SEPARATOR, val);
            if(a.key.keysym.sym == SDLK_MINUS) i->setkey(KEY_SUBTRACT, val);
//                if(a.key.keysym.sym == SDLK_D) i->setkey(KEY_DECIMAL, val);
            if(a.key.keysym.sym == SDLK_SLASH) i->setkey(KEY_DIVIDE, val);
            if(a.key.keysym.sym == SDLK_F1) i->setkey(KEY_F1, val);
            if(a.key.keysym.sym == SDLK_F2) i->setkey(KEY_F2, val);
            if(a.key.keysym.sym == SDLK_F3) i->setkey(KEY_F3, val);
            if(a.key.keysym.sym == SDLK_F4) i->setkey(KEY_F4, val);
            if(a.key.keysym.sym == SDLK_F5) i->setkey(KEY_F5, val);
            if(a.key.keysym.sym == SDLK_F6) i->setkey(KEY_F6, val);
            if(a.key.keysym.sym == SDLK_F7) i->setkey(KEY_F7, val);
            if(a.key.keysym.sym == SDLK_F8) i->setkey(KEY_F8, val);
            if(a.key.keysym.sym == SDLK_F9) i->setkey(KEY_F9, val);
            if(a.key.keysym.sym == SDLK_F10) i->setkey(KEY_F10, val);
            if(a.key.keysym.sym == SDLK_F11) i->setkey(KEY_F11, val);
            if(a.key.keysym.sym == SDLK_F12) i->setkey(KEY_F12, val);
            if(a.key.keysym.sym == SDLK_F13) i->setkey(KEY_F13, val);
            if(a.key.keysym.sym == SDLK_F14) i->setkey(KEY_F14, val);
            if(a.key.keysym.sym == SDLK_F15) i->setkey(KEY_F15, val);
//            if(a.key.keysym.sym == SDLK_NUMLOCK) i->setkey(KEY_NUMLOCK, val);
//            if(a.key.keysym.sym == SDLK_SCROLLOCK) i->setkey(KEY_SCROLL, val);
            if(a.key.keysym.sym == SDLK_LSHIFT) i->setkey(KEY_LSHIFT, val);
            if(a.key.keysym.sym == SDLK_RSHIFT) i->setkey(KEY_RSHIFT, val);
            if(a.key.keysym.sym == SDLK_LCTRL) i->setkey(KEY_LCONTROL, val);
            if(a.key.keysym.sym == SDLK_RCTRL) i->setkey(KEY_RCONTROL, val);
//            if(a.key.keysym.sym == SDLK_LMETA) i->setkey(KEY_LMENU, val);
//            if(a.key.keysym.sym == SDLK_RMETA) i->setkey(KEY_RMENU, val);
            if(a.key.keysym.sym == SDLK_PLUS) i->setkey(KEY_PLUS, val);
            if(a.key.keysym.sym == SDLK_COMMA) i->setkey(KEY_COMMA, val);
            if(a.key.keysym.sym == SDLK_MINUS) i->setkey(KEY_MINUS, val);
            if(a.key.keysym.sym == SDLK_PERIOD) i->setkey(KEY_PERIOD, val);
            if(a.key.keysym.sym == SDLK_AT) i->setkey(KEY_ATTN, val);
//                if(a.key.keysym.sym == SDLK_c) i->setkey(KEY_CRSEL, val);
//                if(a.key.keysym.sym == SDLK_E) i->setkey(KEY_EXSEL, val);
//                if(a.key.keysym.sym == SDLK_E) i->setkey(KEY_EREOF, val);
//                if(a.key.keysym.sym == SDLK_P) i->setkey(KEY_PLAY, val);
//                if(a.key.keysym.sym == SDLK_Z) i->setkey(KEY_ZOOM, val);
            if(a.key.keysym.sym == SDLK_PAGEUP) i->setkey(KEY_PA1, val);
            if(a.key.keysym.sym == SDLK_CLEAR) i->setkey(KEY_OEM_CLEAR, val);
        }
    }
}
#endif
