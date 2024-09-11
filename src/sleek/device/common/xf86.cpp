#include "xf86.h"
#if defined xf86_device_support

namespace sleek
{
    namespace device
    {
        Device_xf86::Device_xf86(const Device_stub &a) : Device(a)
        {
            GLint SOGL[] = { GLX_RGBA, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None };
            GLint DOGL[] = { GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None };

            display = XOpenDisplay(0);
            int mode = 0, screen = DefaultScreen(display);
            int VideoVersionMinor, VideoVersionMajpr;
            XF86VidModeModeInfo **modes;

            XF86VidModeQueryVersion(display, &VideoVersionMinor, &VideoVersionMajpr);
            XF86VidModeGetAllModeLines(display, screen, &mode, &modes);

            if((vi = glXChooseVisual(display, screen, DOGL)));
            else vi = glXChooseVisual(display, screen, SOGL);

            cx = glXCreateContext(display, vi, 0, GL_TRUE);
            swa.colormap = XCreateColormap(display, RootWindow(display, vi->screen), vi->visual, AllocNone);
            swa.border_pixel = 0;

            XF86VidModeSwitchToMode(display, screen, modes[0]);
            XF86VidModeSetViewPort(display, screen, 0, 0);
            swa.override_redirect = True;
            swa.event_mask = ExposureMask | ButtonPressMask | KeyPressMask | StructureNotifyMask;
            window = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, modes[0]->vdisplay, modes[0]->hdisplay, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &swa);

            XWarpPointer(display, None, window, 0, 0, 0, 0, 0, 0);
            XMapRaised(display, window);
            XGrabKeyboard(display, window, True, GrabModeAsync, GrabModeAsync, CurrentTime );
            XGrabPointer(display, window, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, window, None, CurrentTime);

            glXMakeCurrent(display, window, cx);
            initOpenCL();
            welcomeMessage();
            setVideoSize(info.size);
            enableWindowDecorator(info.decorator);

            printf("Direct Rendering %s\n", glXIsDirect(display, cx) ? "True" : "false");
            printf("=========================================================================\n");
            testGlError();
        }
        
        Device_xf86::~Device_xf86()
        {
            glXMakeCurrent(display, None, 0);
            glXDestroyContext(display, cx);
            XDestroyWindow(display, window);
            XCloseDisplay(display);
        }

        void Device_xf86::setCaption(const std::string &name)
        {
        }

        void Device_xf86::setVideoSize(const math::vector2di &i)
        {
            XResizeWindow(display, window, i.width, i.height);
            Device::setVideoSize(i);
        }

        void Device_xf86::enableWindowDecorator(bool flag)
        {
            Device::enableWindowDecorator(z);
            decorator = flag;
            XFlush(display);
                unsigned char hints[] = { 2, 0, flag };
                Atom property = XInternAtom(display, "_MOTIF_WM_HINTS", true);
                XChangeProperty(display, window, property, property, info.bits, PropModeReplace, hints, 3);
            XSync(display, true);
        }

        void Device_xf86::setGamma(const math::pixel &c)
        {
        }

        void Device_xf86::setFullScreen(bool f)
        {
            Device::setFullScreen(f);
        }

        void Device_xf86::begin(const math::pixel &color)
        {
            if(!reading) return;
            Device::begin(color);
            glClearColor((f32)(color.red/255.f),(f32)(color.green/255.f),(f32)(color.blue/255.f),(f32)(color.alpha/255.f));
            glPushMatrix();
        }

        bool Device_xf86::manage()
        {
            evt->manage(current);
            current->clear();
            running = evt->asRunning;
            return true;
        }

        void Device_xf86::end()
        {
            if(!reading) return;
            glPopMatrix();
            glXSwapBuffers(display, window);
            glFlush();
            Device::end();
            reading = false;
        }

        void Device_xf86::keymap(XEvent a, input *i, bool val)
        {
            auto setkey = [i, val](int k)
            {
                i->key_state[k] = val;
                i->key[k] = true;
            };

            /** event type **/
            if(a.type == KeyPress) i->type = EVENT_KEY_DOWN;
            else if(a.type == KeyRelease) i->type = EVENT_KEY_UP;
            else if(a.type == ButtonPress) i->type = EVENT_MOUSSE_DOWN;
            else if(a.type == ButtonRelease) i->type = EVENT_MOUSSE_UP;
            else if(a.type == MotionNotify) i->type = EVENT_MOUSSE_MOVED;
            else i->type = EVENT_NOTHINK;
            /** mouse event **/
            if(a.xbutton.button == Button1) { i->mouse[MOUSE_LEFT] = true; val=true; setkey(KEY_LBUTTON); }
            if(a.xbutton.button == Button2) { i->mouse[MOUSE_MIDDLE] = true; val=true; setkey(KEY_MBUTTON); }
            if(a.xbutton.button == Button3) { i->mouse[MOUSE_RIGHT] = true; val=true; setkey(KEY_RBUTTON); }
            current->mouse_pos.width = xev.xbutton.x; current->mouse_pos.height = xev.xbutton.y;
            int xkey = XLookupKeysym(&xev.xkey, 0);
            /** key event **/
//                if(xkey == XK_Ca) setkey(KEY_CANCEL);
//                if(xkey == XK_X) setkey(KEY_XBUTTON1);
//                if(xkey == XK_X) setkey(KEY_XBUTTON2);
//                if(xkey == XK_B) setkey(KEY_BACK);
            if(xkey == XK_Tab) setkey(KEY_TAB);
            if(xkey == XK_Clear) setkey(KEY_CLEAR);
            if(xkey == XK_Return) setkey(KEY_RETURN);
            if(xkey == XK_Shift_L || xkey == XK_Shift_R) setkey(KEY_SHIFT);
            if(xkey == XK_Control_L || xkey == XK_Control_R) setkey(KEY_CONTROL);
            if(xkey == XK_Menu) setkey(KEY_MENU);
            if(xkey == XK_Pause) setkey(KEY_PAUSE);
//                if(xkey == XK_C) setkey(KEY_CAPITAL);
            if(xkey == XK_Katakana) setkey(KEY_KANA);
            if(xkey == XK_Hangul) setkey(KEY_HANGUEL);
            if(xkey == XK_Hangul) setkey(KEY_HANGUL);
//                if(xkey == XK_Junja) setkey(KEY_JUNJA);
//                if(xkey == XK_Final) setkey(KEY_FINAL);
            if(xkey == XK_Hangul) setkey(KEY_HANJA);
            if(xkey == XK_Kanji) setkey(KEY_KANJI);
            if(xkey == XK_Escape) setkey(KEY_ESCAPE);
//                if(xkey == XK_Convert) setkey(KEY_CONVERT);
//                if(xkey == XK_NonConvert) setkey(KEY_NONCONVERT);
//                if(xkey == XK_Accept) setkey(KEY_ACCEPT);
            if(xkey == XK_Mode_switch) setkey(KEY_MODECHANGE);
            if(xkey == XK_space) setkey(KEY_SPACE);
//                if(xkey == XK_P) setkey(KEY_PRIOR);
//                if(xkey == XK_N) setkey(KEY_NEXT);
            if(xkey == XK_End) setkey(KEY_END);
            if(xkey == XK_Home) setkey(KEY_HOME);
            if(xkey == XK_Left) setkey(KEY_LEFT);
            if(xkey == XK_Up) setkey(KEY_UP);
            if(xkey == XK_Right) setkey(KEY_RIGHT);
            if(xkey == XK_Down) setkey(KEY_DOWN);
//                if(xkey == XK_S) setkey(KEY_SELECT);
            if(xkey == XK_Print) setkey(KEY_PRINT);
            if(xkey == XK_Execute) setkey(KEY_EXECUT);
//                if(xkey == XK_S) setkey(KEY_SNAPSHOT);
            if(xkey == XK_Insert) setkey(KEY_INSERT);
            if(xkey == XK_Delete) setkey(KEY_DELETE);
            if(xkey == XK_Help) setkey(KEY_HELP);
            if(xkey == XK_0) setkey(KEY_KEY_0);
            if(xkey == XK_1) setkey(KEY_KEY_1);
            if(xkey == XK_2) setkey(KEY_KEY_2);
            if(xkey == XK_3) setkey(KEY_KEY_3);
            if(xkey == XK_4) setkey(KEY_KEY_4);
            if(xkey == XK_5) setkey(KEY_KEY_5);
            if(xkey == XK_6) setkey(KEY_KEY_6);
            if(xkey == XK_7) setkey(KEY_KEY_7);
            if(xkey == XK_8) setkey(KEY_KEY_8);
            if(xkey == XK_9) setkey(KEY_KEY_9);
            if(xkey == XK_a) setkey(KEY_KEY_A);
            if(xkey == XK_b) setkey(KEY_KEY_B);
            if(xkey == XK_c) setkey(KEY_KEY_C);
            if(xkey == XK_d) setkey(KEY_KEY_D);
            if(xkey == XK_e) setkey(KEY_KEY_E);
            if(xkey == XK_f) setkey(KEY_KEY_F);
            if(xkey == XK_g) setkey(KEY_KEY_G);
            if(xkey == XK_h) setkey(KEY_KEY_H);
            if(xkey == XK_i) setkey(KEY_KEY_I);
            if(xkey == XK_j) setkey(KEY_KEY_J);
            if(xkey == XK_k) setkey(KEY_KEY_K);
            if(xkey == XK_l) setkey(KEY_KEY_L);
            if(xkey == XK_m) setkey(KEY_KEY_M);
            if(xkey == XK_n) setkey(KEY_KEY_N);
            if(xkey == XK_o) setkey(KEY_KEY_O);
            if(xkey == XK_p) setkey(KEY_KEY_P);
            if(xkey == XK_q) setkey(KEY_KEY_Q);
            if(xkey == XK_r) setkey(KEY_KEY_R);
            if(xkey == XK_s) setkey(KEY_KEY_S);
            if(xkey == XK_t) setkey(KEY_KEY_T);
            if(xkey == XK_u) setkey(KEY_KEY_U);
            if(xkey == XK_v) setkey(KEY_KEY_V);
            if(xkey == XK_w) setkey(KEY_KEY_W);
            if(xkey == XK_x) setkey(KEY_KEY_X);
            if(xkey == XK_y) setkey(KEY_KEY_Y);
            if(xkey == XK_z) setkey(KEY_KEY_Z);
            if(xkey == XK_Super_L) setkey(KEY_LWIN);
            if(xkey == XK_Super_R) setkey(KEY_RWIN);
//                if(xkey == XK_Apps) setkey(KEY_APPS);
//                if(xkey == XK_Sleep) setkey(KEY_SLEEP);
            if(xkey == XK_KP_0) setkey(KEY_NUMPAD0);
            if(xkey == XK_KP_1) setkey(KEY_NUMPAD1);
            if(xkey == XK_KP_2) setkey(KEY_NUMPAD2);
            if(xkey == XK_KP_3) setkey(KEY_NUMPAD3);
            if(xkey == XK_KP_4) setkey(KEY_NUMPAD4);
            if(xkey == XK_KP_5) setkey(KEY_NUMPAD5);
            if(xkey == XK_KP_6) setkey(KEY_NUMPAD6);
            if(xkey == XK_KP_7) setkey(KEY_NUMPAD7);
            if(xkey == XK_KP_8) setkey(KEY_NUMPAD8);
            if(xkey == XK_KP_9) setkey(KEY_NUMPAD9);
            if(xkey == XK_Multi_key) setkey(KEY_MULTIPLY);
            if(xkey == XK_KP_Add) setkey(KEY_ADD);
            if(xkey == XK_KP_Separator) setkey(KEY_SEPARATOR);
            if(xkey == XK_KP_Subtract) setkey(KEY_SUBTRACT);
            if(xkey == XK_KP_Decimal) setkey(KEY_DECIMAL);
            if(xkey == XK_KP_Divide) setkey(KEY_DIVIDE);
            if(xkey == XK_F1) setkey(KEY_F1);
            if(xkey == XK_F2) setkey(KEY_F2);
            if(xkey == XK_F3) setkey(KEY_F3);
            if(xkey == XK_F4) setkey(KEY_F4);
            if(xkey == XK_F5) setkey(KEY_F5);
            if(xkey == XK_F6) setkey(KEY_F6);
            if(xkey == XK_F7) setkey(KEY_F7);
            if(xkey == XK_F8) setkey(KEY_F8);
            if(xkey == XK_F9) setkey(KEY_F9);
            if(xkey == XK_F10) setkey(KEY_F10);
            if(xkey == XK_F11) setkey(KEY_F11);
            if(xkey == XK_F12) setkey(KEY_F12);
            if(xkey == XK_F13) setkey(KEY_F13);
            if(xkey == XK_F14) setkey(KEY_F14);
            if(xkey == XK_F15) setkey(KEY_F15);
            if(xkey == XK_F16) setkey(KEY_F16);
            if(xkey == XK_F17) setkey(KEY_F17);
            if(xkey == XK_F18) setkey(KEY_F18);
            if(xkey == XK_F19) setkey(KEY_F19);
            if(xkey == XK_F20) setkey(KEY_F20);
            if(xkey == XK_F21) setkey(KEY_F21);
            if(xkey == XK_F22) setkey(KEY_F22);
            if(xkey == XK_F23) setkey(KEY_F23);
            if(xkey == XK_F24) setkey(KEY_F24);
            if(xkey == XK_Num_Lock) setkey(KEY_NUMLOCK);
            if(xkey == XK_Scroll_Lock) setkey(KEY_SCROLL);
            if(xkey == XK_Shift_L) setkey(KEY_LSHIFT);
            if(xkey == XK_Shift_R) setkey(KEY_RSHIFT);
            if(xkey == XK_Control_L) setkey(KEY_LCONTROL);
            if(xkey == XK_Control_R) setkey(KEY_RCONTROL);
            if(xkey == XK_Meta_L) setkey(KEY_LMENU);
            if(xkey == XK_Meta_R) setkey(KEY_RMENU);
            if(xkey == XK_plus) setkey(KEY_PLUS);
            if(xkey == XK_comma) setkey(KEY_COMMA);
            if(xkey == XK_minus) setkey(KEY_MINUS);
            if(xkey == XK_period) setkey(KEY_PERIOD);
//                if(xkey == XK_3270_Attn) setkey(KEY_ATTN);
//                if(xkey == XK_C) setkey(KEY_CRSEL);
//                if(xkey == XK_E) setkey(KEY_EXSEL);
//                if(xkey == XK_E) setkey(KEY_EREOF);
//                if(xkey == XK_P) setkey(KEY_PLAY);
//                if(xkey == XK_Z) setkey(KEY_ZOOM);
            if(xkey == XK_Page_Up) setkey(KEY_PA1);
            if(xkey == XK_Clear) setkey(KEY_OEM_CLEAR);
        }
    }
}
#endif
