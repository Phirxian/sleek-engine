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
            auto setkey = [i, val](int k)
            {
                i->key_state[k] = val;
                i->key[k] = true;
            };
            
            /** event type **/
            if(a.type == SDL_KEYDOWN)
            {
                i->type = EVENT_KEY_DOWN;
                val = true;
            }
            else if(a.type == SDL_KEYUP)
            {
                i->type = EVENT_KEY_UP;
            }
            else if(a.type == SDL_MOUSEBUTTONDOWN)
            {
                i->type = EVENT_MOUSSE_DOWN;
                val = true;
            }
            else if(a.type == SDL_MOUSEBUTTONUP)
            {
                i->type = EVENT_MOUSSE_UP;
            }
            else if(a.type == SDL_MOUSEMOTION)
            {
                i->type = EVENT_MOUSSE_MOVED;
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
            if(a.button.button == SDL_BUTTON_LEFT) { i->mouse[MOUSE_LEFT] = true; setkey(KEY_LBUTTON); }
            if(a.button.button == SDL_BUTTON_MIDDLE) { i->mouse[MOUSE_MIDDLE] = true; setkey(KEY_MBUTTON); }
            if(a.button.button == SDL_BUTTON_RIGHT) { i->mouse[MOUSE_RIGHT] = true; setkey(KEY_RBUTTON); }
            /** key event **/
//                if(a.key.keysym.sym == SDLK_C) setkey(KEY_CANCEL);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_XBUTTON1);
//                if(a.key.keysym.sym == SDLK_X) setkey(KEY_XBUTTON2);
//                if(a.key.keysym.sym == SDLK_B) setkey(KEY_BACK);
            if(a.key.keysym.sym == SDLK_TAB) setkey(KEY_TAB);
            if(a.key.keysym.sym == SDLK_CLEAR) setkey(KEY_CLEAR);
            if(a.key.keysym.sym == SDLK_RETURN) setkey(KEY_RETURN);
            if(a.key.keysym.sym == SDLK_RSHIFT || a.key.keysym.sym == SDLK_LSHIFT) setkey(KEY_SHIFT);
            if(a.key.keysym.sym == SDLK_RCTRL || a.key.keysym.sym == SDLK_LCTRL) setkey(KEY_CONTROL);
            if(a.key.keysym.sym == SDLK_MENU) setkey(KEY_MENU);
            if(a.key.keysym.sym == SDLK_PAUSE) setkey(KEY_PAUSE);
//                if(a.key.keysym.sym == SDLK_C) setkey(KEY_CAPITAL);
//                if(a.key.keysym.sym == SDLK_K) setkey(KEY_KANA);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_HANGUEL);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_HANGUL);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_JUNJA);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_FINAL);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_HANJA);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_KANJI);
            if(a.key.keysym.sym == SDLK_ESCAPE) setkey(KEY_ESCAPE);
//                if(a.key.keysym.sym == SDLK_C) setkey(KEY_CONVERT);
//                if(a.key.keysym.sym == SDLK_N) setkey(KEY_NONCONVERT);
//                if(a.key.keysym.sym == SDLK_A) setkey(KEY_ACCEPT);
            if(a.key.keysym.sym == SDLK_MODE) setkey(KEY_MODECHANGE);
            if(a.key.keysym.sym == SDLK_SPACE) setkey(KEY_SPACE);
//                if(a.key.keysym.sym == SDLK_P) setkey(KEY_PRIOR);
//                if(a.key.keysym.sym == SDLK_N) setkey(KEY_NEXT);
            if(a.key.keysym.sym == SDLK_END) setkey(KEY_END);
            if(a.key.keysym.sym == SDLK_HOME) setkey(KEY_HOME);
            if(a.key.keysym.sym == SDLK_LEFT) setkey(KEY_LEFT);
            if(a.key.keysym.sym == SDLK_UP) setkey(KEY_UP);
            if(a.key.keysym.sym == SDLK_RIGHT) setkey(KEY_RIGHT);
            if(a.key.keysym.sym == SDLK_DOWN) setkey(KEY_DOWN);
//                if(a.key.keysym.sym == SDLK_S) setkey(KEY_SELECT);
//            if(a.key.keysym.sym == SDLK_PRINT) setkey(KEY_PRINT);
//                if(a.key.keysym.sym == SDLK_E) setkey(KEY_EXECUT);
//                if(a.key.keysym.sym == SDLK_S) setkey(KEY_SNAPSHOT);
            if(a.key.keysym.sym == SDLK_INSERT) setkey(KEY_INSERT);
            if(a.key.keysym.sym == SDLK_DELETE) setkey(KEY_DELETE);
            if(a.key.keysym.sym == SDLK_HELP) setkey(KEY_HELP);
            if(a.key.keysym.sym == SDLK_0) setkey(KEY_KEY_0);
            if(a.key.keysym.sym == SDLK_1) setkey(KEY_KEY_1);
            if(a.key.keysym.sym == SDLK_2) setkey(KEY_KEY_2);
            if(a.key.keysym.sym == SDLK_3) setkey(KEY_KEY_3);
            if(a.key.keysym.sym == SDLK_4) setkey(KEY_KEY_4);
            if(a.key.keysym.sym == SDLK_5) setkey(KEY_KEY_5);
            if(a.key.keysym.sym == SDLK_6) setkey(KEY_KEY_6);
            if(a.key.keysym.sym == SDLK_7) setkey(KEY_KEY_7);
            if(a.key.keysym.sym == SDLK_8) setkey(KEY_KEY_8);
            if(a.key.keysym.sym == SDLK_9) setkey(KEY_KEY_9);
            if(a.key.keysym.sym == SDLK_a) setkey(KEY_KEY_A);
            if(a.key.keysym.sym == SDLK_b) setkey(KEY_KEY_B);
            if(a.key.keysym.sym == SDLK_c) setkey(KEY_KEY_C);
            if(a.key.keysym.sym == SDLK_d) setkey(KEY_KEY_D);
            if(a.key.keysym.sym == SDLK_e) setkey(KEY_KEY_E);
            if(a.key.keysym.sym == SDLK_f) setkey(KEY_KEY_F);
            if(a.key.keysym.sym == SDLK_g) setkey(KEY_KEY_G);
            if(a.key.keysym.sym == SDLK_h) setkey(KEY_KEY_H);
            if(a.key.keysym.sym == SDLK_i) setkey(KEY_KEY_I);
            if(a.key.keysym.sym == SDLK_j) setkey(KEY_KEY_J);
            if(a.key.keysym.sym == SDLK_k) setkey(KEY_KEY_K);
            if(a.key.keysym.sym == SDLK_l) setkey(KEY_KEY_L);
            if(a.key.keysym.sym == SDLK_m) setkey(KEY_KEY_M);
            if(a.key.keysym.sym == SDLK_n) setkey(KEY_KEY_N);
            if(a.key.keysym.sym == SDLK_o) setkey(KEY_KEY_O);
            if(a.key.keysym.sym == SDLK_p) setkey(KEY_KEY_P);
            if(a.key.keysym.sym == SDLK_q) setkey(KEY_KEY_Q);
            if(a.key.keysym.sym == SDLK_r) setkey(KEY_KEY_R);
            if(a.key.keysym.sym == SDLK_s) setkey(KEY_KEY_S);
            if(a.key.keysym.sym == SDLK_t) setkey(KEY_KEY_T);
            if(a.key.keysym.sym == SDLK_u) setkey(KEY_KEY_U);
            if(a.key.keysym.sym == SDLK_v) setkey(KEY_KEY_V);
            if(a.key.keysym.sym == SDLK_w) setkey(KEY_KEY_W);
            if(a.key.keysym.sym == SDLK_x) setkey(KEY_KEY_X);
            if(a.key.keysym.sym == SDLK_y) setkey(KEY_KEY_Y);
            if(a.key.keysym.sym == SDLK_z) setkey(KEY_KEY_Z);
//            if(a.key.keysym.sym == SDLK_LMETA) setkey(KEY_LWIN);
//            if(a.key.keysym.sym == SDLK_RMETA) setkey(KEY_RWIN);
//                if(a.key.keysym.sym == SDLK_A) setkey(KEY_APPS);
//                if(a.key.keysym.sym == SDLK_S) setkey(KEY_SLEEP);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_NUMPAD0);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_NUMPAD1);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_NUMPAD2);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_NUMPAD3);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_NUMPAD4);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_NUMPAD5);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_NUMPAD6);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_NUMPAD7);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_NUMPAD8);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_NUMPAD9);
            if(a.key.keysym.sym == SDLK_ASTERISK) setkey(KEY_MULTIPLY);
//                if(a.key.keysym.sym == SDLK_) setkey(KEY_ADD);
//                if(a.key.keysym.sym == SDLK_s) setkey(KEY_SEPARATOR);
            if(a.key.keysym.sym == SDLK_MINUS) setkey(KEY_SUBTRACT);
//                if(a.key.keysym.sym == SDLK_D) setkey(KEY_DECIMAL);
            if(a.key.keysym.sym == SDLK_SLASH) setkey(KEY_DIVIDE);
            if(a.key.keysym.sym == SDLK_F1) setkey(KEY_F1);
            if(a.key.keysym.sym == SDLK_F2) setkey(KEY_F2);
            if(a.key.keysym.sym == SDLK_F3) setkey(KEY_F3);
            if(a.key.keysym.sym == SDLK_F4) setkey(KEY_F4);
            if(a.key.keysym.sym == SDLK_F5) setkey(KEY_F5);
            if(a.key.keysym.sym == SDLK_F6) setkey(KEY_F6);
            if(a.key.keysym.sym == SDLK_F7) setkey(KEY_F7);
            if(a.key.keysym.sym == SDLK_F8) setkey(KEY_F8);
            if(a.key.keysym.sym == SDLK_F9) setkey(KEY_F9);
            if(a.key.keysym.sym == SDLK_F10) setkey(KEY_F10);
            if(a.key.keysym.sym == SDLK_F11) setkey(KEY_F11);
            if(a.key.keysym.sym == SDLK_F12) setkey(KEY_F12);
            if(a.key.keysym.sym == SDLK_F13) setkey(KEY_F13);
            if(a.key.keysym.sym == SDLK_F14) setkey(KEY_F14);
            if(a.key.keysym.sym == SDLK_F15) setkey(KEY_F15);
//            if(a.key.keysym.sym == SDLK_NUMLOCK) setkey(KEY_NUMLOCK);
//            if(a.key.keysym.sym == SDLK_SCROLLOCK) setkey(KEY_SCROLL);
            if(a.key.keysym.sym == SDLK_LSHIFT) setkey(KEY_LSHIFT);
            if(a.key.keysym.sym == SDLK_RSHIFT) setkey(KEY_RSHIFT);
            if(a.key.keysym.sym == SDLK_LCTRL) setkey(KEY_LCONTROL);
            if(a.key.keysym.sym == SDLK_RCTRL) setkey(KEY_RCONTROL);
//            if(a.key.keysym.sym == SDLK_LMETA) setkey(KEY_LMENU);
//            if(a.key.keysym.sym == SDLK_RMETA) setkey(KEY_RMENU);
            if(a.key.keysym.sym == SDLK_PLUS) setkey(KEY_PLUS);
            if(a.key.keysym.sym == SDLK_COMMA) setkey(KEY_COMMA);
            if(a.key.keysym.sym == SDLK_MINUS) setkey(KEY_MINUS);
            if(a.key.keysym.sym == SDLK_PERIOD) setkey(KEY_PERIOD);
            if(a.key.keysym.sym == SDLK_AT) setkey(KEY_ATTN);
//                if(a.key.keysym.sym == SDLK_c) setkey(KEY_CRSEL);
//                if(a.key.keysym.sym == SDLK_E) setkey(KEY_EXSEL);
//                if(a.key.keysym.sym == SDLK_E) setkey(KEY_EREOF);
//                if(a.key.keysym.sym == SDLK_P) setkey(KEY_PLAY);
//                if(a.key.keysym.sym == SDLK_Z) setkey(KEY_ZOOM);
            if(a.key.keysym.sym == SDLK_PAGEUP) setkey(KEY_PA1);
            if(a.key.keysym.sym == SDLK_CLEAR) setkey(KEY_OEM_CLEAR);
        }
    }
}
#endif
