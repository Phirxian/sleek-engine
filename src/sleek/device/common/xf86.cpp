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
        void Device_xf86::keymap(XEvent a, input *i)
        {
            /** event type **/
            if(a.type == KeyPress) i->type = EVENT_KEY_DOWN;
            else if(a.type == KeyRelease) i->type = EVENT_KEY_UP;
            else if(a.type == ButtonPress) i->type = EVENT_MOUSSE_DOWN;
            else if(a.type == ButtonRelease) i->type = EVENT_MOUSSE_UP;
            else if(a.type == MotionNotify) i->type = EVENT_MOUSSE_MOVED;
            else i->type = EVENT_NOTHINK;
            /** mouse event **/
            if(a.xbutton.button == Button1) { i->mouse[MOUSE_LEFT] = true; i->key[KEY_LBUTTON] = true; }
            if(a.xbutton.button == Button2) { i->mouse[MOUSE_MIDDLE] = true; i->key[KEY_MBUTTON] = true; }
            if(a.xbutton.button == Button3) { i->mouse[MOUSE_RIGHT] = true; i->key[KEY_RBUTTON] = true; }
            current->mouse_pos.width = xev.xbutton.x; current->mouse_pos.height = xev.xbutton.y;
            int xkey = XLookupKeysym(&xev.xkey, 0);
            /** key event **/
//                if(xkey == XK_Ca) i->key[KEY_CANCEL] = true;
//                if(xkey == XK_X) i->key[KEY_XBUTTON1] = true;
//                if(xkey == XK_X) i->key[KEY_XBUTTON2] = true;
//                if(xkey == XK_B) i->key[KEY_BACK] = true;
            if(xkey == XK_Tab) i->key[KEY_TAB] = true;
            if(xkey == XK_Clear) i->key[KEY_CLEAR] = true;
            if(xkey == XK_Return) i->key[KEY_RETURN] = true;
            if(xkey == XK_Shift_L || xkey == XK_Shift_R) i->key[KEY_SHIFT] = true;
            if(xkey == XK_Control_L || xkey == XK_Control_R) i->key[KEY_CONTROL] = true;
            if(xkey == XK_Menu) i->key[KEY_MENU] = true;
            if(xkey == XK_Pause) i->key[KEY_PAUSE] = true;
//                if(xkey == XK_C) i->key[KEY_CAPITAL] = true;
            if(xkey == XK_Katakana) i->key[KEY_KANA] = true;
            if(xkey == XK_Hangul) i->key[KEY_HANGUEL] = true;
            if(xkey == XK_Hangul) i->key[KEY_HANGUL] = true;
//                if(xkey == XK_Junja) i->key[KEY_JUNJA] = true;
//                if(xkey == XK_Final) i->key[KEY_FINAL] = true;
            if(xkey == XK_Hangul) i->key[KEY_HANJA] = true;
            if(xkey == XK_Kanji) i->key[KEY_KANJI] = true;
            if(xkey == XK_Escape) i->key[KEY_ESCAPE] = true;
//                if(xkey == XK_Convert) i->key[KEY_CONVERT] = true;
//                if(xkey == XK_NonConvert) i->key[KEY_NONCONVERT] = true;
//                if(xkey == XK_Accept) i->key[KEY_ACCEPT] = true;
            if(xkey == XK_Mode_switch) i->key[KEY_MODECHANGE] = true;
            if(xkey == XK_space) i->key[KEY_SPACE] = true;
//                if(xkey == XK_P) i->key[KEY_PRIOR] = true;
//                if(xkey == XK_N) i->key[KEY_NEXT] = true;
            if(xkey == XK_End) i->key[KEY_END] = true;
            if(xkey == XK_Home) i->key[KEY_HOME] = true;
            if(xkey == XK_Left) i->key[KEY_LEFT] = true;
            if(xkey == XK_Up) i->key[KEY_UP] = true;
            if(xkey == XK_Right) i->key[KEY_RIGHT] = true;
            if(xkey == XK_Down) i->key[KEY_DOWN] = true;
//                if(xkey == XK_S) i->key[KEY_SELECT] = true;
            if(xkey == XK_Print) i->key[KEY_PRINT] = true;
            if(xkey == XK_Execute) i->key[KEY_EXECUT] = true;
//                if(xkey == XK_S) i->key[KEY_SNAPSHOT] = true;
            if(xkey == XK_Insert) i->key[KEY_INSERT] = true;
            if(xkey == XK_Delete) i->key[KEY_DELETE] = true;
            if(xkey == XK_Help) i->key[KEY_HELP] = true;
            if(xkey == XK_0) i->key[KEY_KEY_0] = true;
            if(xkey == XK_1) i->key[KEY_KEY_1] = true;
            if(xkey == XK_2) i->key[KEY_KEY_2] = true;
            if(xkey == XK_3) i->key[KEY_KEY_3] = true;
            if(xkey == XK_4) i->key[KEY_KEY_4] = true;
            if(xkey == XK_5) i->key[KEY_KEY_5] = true;
            if(xkey == XK_6) i->key[KEY_KEY_6] = true;
            if(xkey == XK_7) i->key[KEY_KEY_7] = true;
            if(xkey == XK_8) i->key[KEY_KEY_8] = true;
            if(xkey == XK_9) i->key[KEY_KEY_9] = true;
            if(xkey == XK_a) i->key[KEY_KEY_A] = true;
            if(xkey == XK_b) i->key[KEY_KEY_B] = true;
            if(xkey == XK_c) i->key[KEY_KEY_C] = true;
            if(xkey == XK_d) i->key[KEY_KEY_D] = true;
            if(xkey == XK_e) i->key[KEY_KEY_E] = true;
            if(xkey == XK_f) i->key[KEY_KEY_F] = true;
            if(xkey == XK_g) i->key[KEY_KEY_G] = true;
            if(xkey == XK_h) i->key[KEY_KEY_H] = true;
            if(xkey == XK_i) i->key[KEY_KEY_I] = true;
            if(xkey == XK_j) i->key[KEY_KEY_J] = true;
            if(xkey == XK_k) i->key[KEY_KEY_K] = true;
            if(xkey == XK_l) i->key[KEY_KEY_L] = true;
            if(xkey == XK_m) i->key[KEY_KEY_M] = true;
            if(xkey == XK_n) i->key[KEY_KEY_N] = true;
            if(xkey == XK_o) i->key[KEY_KEY_O] = true;
            if(xkey == XK_p) i->key[KEY_KEY_P] = true;
            if(xkey == XK_q) i->key[KEY_KEY_Q] = true;
            if(xkey == XK_r) i->key[KEY_KEY_R] = true;
            if(xkey == XK_s) i->key[KEY_KEY_S] = true;
            if(xkey == XK_t) i->key[KEY_KEY_T] = true;
            if(xkey == XK_u) i->key[KEY_KEY_U] = true;
            if(xkey == XK_v) i->key[KEY_KEY_V] = true;
            if(xkey == XK_w) i->key[KEY_KEY_W] = true;
            if(xkey == XK_x) i->key[KEY_KEY_X] = true;
            if(xkey == XK_y) i->key[KEY_KEY_Y] = true;
            if(xkey == XK_z) i->key[KEY_KEY_Z] = true;
            if(xkey == XK_Super_L) i->key[KEY_LWIN] = true;
            if(xkey == XK_Super_R) i->key[KEY_RWIN] = true;
//                if(xkey == XK_Apps) i->key[KEY_APPS] = true;
//                if(xkey == XK_Sleep) i->key[KEY_SLEEP] = true;
            if(xkey == XK_KP_0) i->key[KEY_NUMPAD0] = true;
            if(xkey == XK_KP_1) i->key[KEY_NUMPAD1] = true;
            if(xkey == XK_KP_2) i->key[KEY_NUMPAD2] = true;
            if(xkey == XK_KP_3) i->key[KEY_NUMPAD3] = true;
            if(xkey == XK_KP_4) i->key[KEY_NUMPAD4] = true;
            if(xkey == XK_KP_5) i->key[KEY_NUMPAD5] = true;
            if(xkey == XK_KP_6) i->key[KEY_NUMPAD6] = true;
            if(xkey == XK_KP_7) i->key[KEY_NUMPAD7] = true;
            if(xkey == XK_KP_8) i->key[KEY_NUMPAD8] = true;
            if(xkey == XK_KP_9) i->key[KEY_NUMPAD9] = true;
            if(xkey == XK_Multi_key) i->key[KEY_MULTIPLY] = true;
            if(xkey == XK_KP_Add) i->key[KEY_ADD] = true;
            if(xkey == XK_KP_Separator) i->key[KEY_SEPARATOR] = true;
            if(xkey == XK_KP_Subtract) i->key[KEY_SUBTRACT] = true;
            if(xkey == XK_KP_Decimal) i->key[KEY_DECIMAL] = true;
            if(xkey == XK_KP_Divide) i->key[KEY_DIVIDE] = true;
            if(xkey == XK_F1) i->key[KEY_F1] = true;
            if(xkey == XK_F2) i->key[KEY_F2] = true;
            if(xkey == XK_F3) i->key[KEY_F3] = true;
            if(xkey == XK_F4) i->key[KEY_F4] = true;
            if(xkey == XK_F5) i->key[KEY_F5] = true;
            if(xkey == XK_F6) i->key[KEY_F6] = true;
            if(xkey == XK_F7) i->key[KEY_F7] = true;
            if(xkey == XK_F8) i->key[KEY_F8] = true;
            if(xkey == XK_F9) i->key[KEY_F9] = true;
            if(xkey == XK_F10) i->key[KEY_F10] = true;
            if(xkey == XK_F11) i->key[KEY_F11] = true;
            if(xkey == XK_F12) i->key[KEY_F12] = true;
            if(xkey == XK_F13) i->key[KEY_F13] = true;
            if(xkey == XK_F14) i->key[KEY_F14] = true;
            if(xkey == XK_F15) i->key[KEY_F15] = true;
            if(xkey == XK_F16) i->key[KEY_F16] = true;
            if(xkey == XK_F17) i->key[KEY_F17] = true;
            if(xkey == XK_F18) i->key[KEY_F18] = true;
            if(xkey == XK_F19) i->key[KEY_F19] = true;
            if(xkey == XK_F20) i->key[KEY_F20] = true;
            if(xkey == XK_F21) i->key[KEY_F21] = true;
            if(xkey == XK_F22) i->key[KEY_F22] = true;
            if(xkey == XK_F23) i->key[KEY_F23] = true;
            if(xkey == XK_F24) i->key[KEY_F24] = true;
            if(xkey == XK_Num_Lock) i->key[KEY_NUMLOCK] = true;
            if(xkey == XK_Scroll_Lock) i->key[KEY_SCROLL] = true;
            if(xkey == XK_Shift_L) i->key[KEY_LSHIFT] = true;
            if(xkey == XK_Shift_R) i->key[KEY_RSHIFT] = true;
            if(xkey == XK_Control_L) i->key[KEY_LCONTROL] = true;
            if(xkey == XK_Control_R) i->key[KEY_RCONTROL] = true;
            if(xkey == XK_Meta_L) i->key[KEY_LMENU] = true;
            if(xkey == XK_Meta_R) i->key[KEY_RMENU] = true;
            if(xkey == XK_plus) i->key[KEY_PLUS] = true;
            if(xkey == XK_comma) i->key[KEY_COMMA] = true;
            if(xkey == XK_minus) i->key[KEY_MINUS] = true;
            if(xkey == XK_period) i->key[KEY_PERIOD] = true;
//                if(xkey == XK_3270_Attn) i->key[KEY_ATTN] = true;
//                if(xkey == XK_C) i->key[KEY_CRSEL] = true;
//                if(xkey == XK_E) i->key[KEY_EXSEL] = true;
//                if(xkey == XK_E) i->key[KEY_EREOF] = true;
//                if(xkey == XK_P) i->key[KEY_PLAY] = true;
//                if(xkey == XK_Z) i->key[KEY_ZOOM] = true;
            if(xkey == XK_Page_Up) i->key[KEY_PA1] = true;
            if(xkey == XK_Clear) i->key[KEY_OEM_CLEAR] = true;
        }
    }
}
#endif
