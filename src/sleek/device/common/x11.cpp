#include "x11.h"
#if defined x11_device_support

#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>

namespace sleek
{
    struct Hints
    {
        u64   flags;
        u64   functions;
        u64   decorations;
        long  inputMode;
        u64   status;
    };

    namespace device
    {
        Device_x11::Device_x11(const Device_stub &a) noexcept : Device(a)
        {
            GLint SOGL[] = { GLX_RGBA, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None };
            GLint DOGL[] = { GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None };

            display = XOpenDisplay(0);
            if(!display)
            {
                printf("Programme need X session\n");
                return;
            }

            running = true;

            if((vi = glXChooseVisual(display, DefaultScreen(display), DOGL)));
            else vi = glXChooseVisual(display, DefaultScreen(display), SOGL);


            int fbcount = 0;

            if((fb = glXChooseFBConfig(display, DefaultScreen(display), DOGL+1, &fbcount)));
            else fb = glXChooseFBConfig(display, DefaultScreen(display), SOGL+1, &fbcount);

            if(!fb || fbcount == 0)
                printf("no fbconfig to select\n");

            swa.colormap = XCreateColormap(display, RootWindow(display, vi->screen), vi->visual, AllocNone);
            swa.border_pixel = 0;
            swa.event_mask = ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask | FocusChangeMask | PointerMotionMask;
            window = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, info.size.x, info.size.y, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &swa);

            Atom wxdelete = XInternAtom(display, "WM_DELETE_WINDOW", True);
            XSetWMProtocols(display, window, &wxdelete, 1);
            XSetStandardProperties(display, window, "", "", None, 0, 0, 0);
            XMapRaised(display, window);

            welcomeMessage();
            CreateX11Cursor();
            setVideoSize(info.size);
            enableWindowDecorator(info.decorator);

            info.visual = vi;
            info.fbconfig = fb;
            info.display = display;
            info.window = &window;
        }

        Device_x11::~Device_x11() noexcept
        {
            XDestroyWindow(display, window);
            XCloseDisplay(display);
        }

        void Device_x11::setCaption(const std::string &name) noexcept
        {
//            if(!info.decorator) return;
//            wchar_t *tmp[] = { os::charToWchar_t(name.c_str()), 0 };
//
//            XTextProperty txt;
//            XwcTextListToTextProperty(display, tmp, 1, XStdICCTextStyle, &txt);
//            XSetWMName(display, window, &txt);
//            XSetWMIconName(display, window, &txt);
            XStoreName(display, window, name.c_str());
            Device::setCaption(name);
        }

        void Device_x11::setVideoSize(const math::vec2i &i) noexcept
        {
            XFlush(display);
            XResizeWindow(display, window, i.x, i.y);
            Device::setVideoSize(i);
            XSync(display, true);
        }

        void Device_x11::setWindowPos(const math::vec2i &i) noexcept
        {
            XFlush(display);
            XMoveWindow(display, window, i.x, i.y);
            XSync(display, true);
        }

        math::vec2i Device_x11::getDesktopVideoSize() const noexcept
        {
            return math::vec2i(
                DefaultScreenOfDisplay(display)->width,
                DefaultScreenOfDisplay(display)->height
            );
        }

        void Device_x11::enableWindowDecorator(bool flag) noexcept
        {
            Device::enableWindowDecorator(flag);
            XFlush(display);
                if(flag)
                {
                    unsigned char hints[] = { 0, 0, flag };
                    Atom property = XInternAtom(display, "_MOTIF_WM_HINTS", true);
                    XChangeProperty(display, window, property, property, info.bits, PropModeReplace, hints, 3);
                }
                else
                {
                    unsigned char hints[] = { 2, 0, flag };
                    Atom property = XInternAtom(display, "_MOTIF_WM_HINTS", true);
                    XChangeProperty(display, window, property, property, info.bits, PropModeReplace, hints, 3);
                }
            XSync(display, true);
        }

        void Device_x11::setGamma(const math::pixel &c) noexcept
        {
        }

        void Device_x11::setFullScreen(bool f) noexcept
        {
            if(info.fullscreen == f)
                return;

            Device::setFullScreen(f);

            Hints hints;
                // Specify that we're changing the window decorations.
                hints.flags = 2;
                hints.decorations = !f;
            Atom property;

            property = XInternAtom(display,"_MOTIF_WM_HINTS",true);
            XChangeProperty(display, window,property,property,32,PropModeReplace,(u8*)&hints,5);

            s32 modeCount;
            XF86VidModeModeInfo** modes;
            XF86VidModeGetAllModeLines(display, DefaultScreen(display), &modeCount, &modes);

            s32 bestMode = -1;
            if(f)
            {
                XMoveWindow(display, window, 0, 0);
                for(s32 i = 0; i<modeCount; ++i)
                {
                    if(bestMode==-1 && modes[i]->hdisplay >= info.size.x && modes[i]->vdisplay >= info.size.y)
                        bestMode = i;

                    else if(bestMode!=-1 &&
                            modes[i]->hdisplay >= info.size.x &&
                            modes[i]->vdisplay >= info.size.y &&
                            modes[i]->hdisplay <= modes[bestMode]->hdisplay &&
                            modes[i]->vdisplay <= modes[bestMode]->vdisplay)
                    bestMode = i;
                }
            }
            else
            {
                Screen *scr = XDefaultScreenOfDisplay(display);
                for(s32 i = 0; i<modeCount; ++i)
                {
                    if(bestMode==-1 && modes[i]->hdisplay >= WidthOfScreen(scr) && modes[i]->vdisplay >= HeightOfScreen(scr))
                        bestMode = i;
                    else if(bestMode!=-1 &&
                            modes[i]->hdisplay >= WidthOfScreen(scr) &&
                            modes[i]->vdisplay >= HeightOfScreen(scr) &&
                            modes[i]->hdisplay <= modes[bestMode]->hdisplay &&
                            modes[i]->vdisplay <= modes[bestMode]->vdisplay)
                        bestMode = i;
                }
                math::vec2u pos(WidthOfScreen(scr), HeightOfScreen(scr));
                    pos -= getDesktopVideoSize();
                    pos /= 2;
                XMoveWindow(display, window, pos.x, pos.y);
            }
            printf("fullscreen switch mode %d/%d\n", bestMode, modeCount);
            //XGrabPointer(display,window,false,0,GrabModeAsync,GrabModeAsync,window,0L,CurrentTime);
            //XGrabKeyboard(display,window,false,GrabModeAsync,GrabModeAsync,CurrentTime);

            XF86VidModeSwitchToMode(display, DefaultScreen(display), modes[bestMode]);
            XF86VidModeSetViewPort(display,DefaultScreen(display), 0, 0);
            XRaiseWindow(display, window);
            XFlush(display);
            XFree(modes);
        }

        void Device_x11::WarpMouse(const math::vec2i &i) noexcept
        {
            XWarpPointer(display, None, window, 0, 0, 0, 0, i.x, i.y);
        }

        void Device_x11::ShowMouse(bool i) noexcept
        {
            if(i) XUndefineCursor(display, window);
            else XDefineCursor(display, window, invisCursor);
        }

        bool Device_x11::run() noexcept
        {
            while(XPending(display)>0 && display && running)
            {
                XEvent xev;
                XNextEvent(display, &xev);
                switch(xev.type)
                {
                    case Expose:
                    case ConfigureNotify:
                    {
                        auto newsize = math::vec2i(xev.xconfigurerequest.width, xev.xconfigurerequest.height);
                        if(newsize.x > 0 || newsize.y > 0)
                            if(info.size.x != newsize.x || info.size.y != newsize.x)
                                Device::setVideoSize(newsize);
                        current->type = EVENT_WINDOW_RESIZE;
                        evt->manage(current);
                        current->clear();
                    }
                    break;
                    case MapNotify:
                    break;
                    case UnmapNotify:
                    break;
                    case FocusIn:
                    break;
                    case FocusOut:
                    break;
                    case MotionNotify:
                        current->type = EVENT_MOUSSE_MOVED;
                        current->mouse_pos.x = xev.xbutton.x;
                        current->mouse_pos.y = xev.xbutton.y;
                        evt->manage(current);
                        current->clear();
                    break;
                    case MappingNotify:
                        XRefreshKeyboardMapping(&xev.xmapping);
                    break;
                    case ClientMessage:
                        current->exit_msg = true;
                        evt->manage(current);
                        current->clear();
                    break;
                    case SelectionRequest:
                    break;
                    case KeyPress:
                        current->type = EVENT_KEY_DOWN;
                        keymap(xev, current, true);
                        evt->manage(current);
                        current->clear();
                    break;
                    case KeyRelease:
                        current->type = EVENT_KEY_UP;
                        keymap(xev, current, false);
                        evt->manage(current);
                        current->clear();
                    break;
                    case ButtonPress:
                        current->type = EVENT_MOUSSE_DOWN;
                        keymap(xev, current, true);
                        evt->manage(current);
                        current->clear();
                    break;
                    case ButtonRelease:
                        current->type = EVENT_MOUSSE_UP;
                        keymap(xev, current, false);
                        evt->manage(current);
                        current->clear();
                    break;
                }
            }
            reading = true;
            return Device::run();
        }

        void Device_x11::begin() noexcept
        {
            if(!reading) return;
            Device::begin();
        }

        bool Device_x11::manage() noexcept
        {
            running = evt->asRunning;
            return true;
        }

        void Device_x11::end() noexcept
        {
            if(!reading) return;
            Device::end();
            reading = false;
            glXSwapBuffers((Display*)getInfo().display, *(Window*)getInfo().window);
        }

        void Device_x11::CreateX11Cursor() noexcept
        {
            XGCValues values;
            unsigned long valuemask = 0;

            XColor fg, bg;

            Pixmap invisBitmap = XCreatePixmap(display, window, 32, 32, 1);
            Pixmap maskBitmap = XCreatePixmap(display, window, 32, 32, 1);
            Colormap screen_colormap = DefaultColormap( display, DefaultScreen( display ) );
            XAllocNamedColor( display, screen_colormap, "black", &fg, &fg );
            XAllocNamedColor( display, screen_colormap, "white", &bg, &bg );

            GC gc = XCreateGC( display, invisBitmap, valuemask, &values );

            XSetForeground( display, gc, BlackPixel( display, DefaultScreen( display ) ) );
            XFillRectangle( display, invisBitmap, gc, 0, 0, 32, 32 );
            XFillRectangle( display, maskBitmap, gc, 0, 0, 32, 32 );

            invisCursor = XCreatePixmapCursor( display, invisBitmap, maskBitmap, &fg, &bg, 1, 1 );
            XFreeGC(display, gc);
            XFreePixmap(display, invisBitmap);
            XFreePixmap(display, maskBitmap);
        }

        void Device_x11::keymap(XEvent a, input *i, bool val) noexcept
        {
            if(a.xbutton.button == Button1) { i->mouse[MOUSE_LEFT] = true; val=true; i->setkey(KEY_LBUTTON, val); }
            if(a.xbutton.button == Button2) { i->mouse[MOUSE_MIDDLE] = true; val=true; i->setkey(KEY_MBUTTON, val); }
            if(a.xbutton.button == Button3) { i->mouse[MOUSE_RIGHT] = true;  val=true; i->setkey(KEY_RBUTTON, val); }
            if(a.xbutton.button == Button4) { i->mouse[MOUSE_WHEEL_UP] = true;   }
            if(a.xbutton.button == Button5) { i->mouse[MOUSE_WHEEL_DOWN] = true; }

            int xkey = XLookupKeysym(&a.xkey, 0);
            /** key event **/
//                if(xkey == XK_Ca) i->setkey(KEY_CANCEL, val);
            i->key[KEY_XBUTTON1] = xkey == XK_X;
            i->key[KEY_XBUTTON2] = xkey == XK_X;
            
            if(xkey == XK_B) i->setkey(KEY_BACK, val);
            if(xkey == XK_Tab) i->setkey(KEY_TAB, val);
            if(xkey == XK_Clear) i->setkey(KEY_CLEAR, val);
            if(xkey == XK_Return) i->setkey(KEY_RETURN, val);
            if(xkey == XK_Shift_L || xkey == XK_Shift_R) i->setkey(KEY_SHIFT, val);
            if(xkey == XK_Control_L || xkey == XK_Control_R) i->setkey(KEY_CONTROL, val);
            if(xkey == XK_Menu) i->setkey(KEY_MENU, val);
            if(xkey == XK_Pause) i->setkey(KEY_PAUSE, val);
            if(xkey == XK_C) i->setkey(KEY_CAPITAL, val);
            if(xkey == XK_Katakana) i->setkey(KEY_KANA, val);
//                if(xkey == XK_Hangul) i->setkey(KEY_HANGUEL, val);
//                if(xkey == XK_Hangul) i->setkey(KEY_HANGUL, val);
//                if(xkey == XK_Junja) i->setkey(KEY_JUNJA, val);
//                if(xkey == XK_Final) i->setkey(KEY_FINAL, val);
//                if(xkey == XK_Hangul) i->setkey(KEY_HANJA, val);
            if(xkey == XK_Kanji) i->setkey(KEY_KANJI, val);
            if(xkey == XK_Escape) i->setkey(KEY_ESCAPE, val);
//                if(xkey == XK_Convert) i->setkey(KEY_CONVERT, val);
//                if(xkey == XK_NonConvert) i->setkey(KEY_NONCONVERT, val);
//                if(xkey == XK_Accept) i->setkey(KEY_ACCEPT, val);
            if(xkey == XK_Mode_switch) i->setkey(KEY_MODECHANGE, val);
            if(xkey == XK_space) i->setkey(KEY_SPACE, val);
            if(xkey == XK_P) i->setkey(KEY_PRIOR, val);
            if(xkey == XK_N) i->setkey(KEY_NEXT, val);
            if(xkey == XK_End) i->setkey(KEY_END, val);
            if(xkey == XK_Home) i->setkey(KEY_HOME, val);
            if(xkey == XK_Left) i->setkey(KEY_LEFT, val);
            if(xkey == XK_Up) i->setkey(KEY_UP, val);
            if(xkey == XK_Right) i->setkey(KEY_RIGHT, val);
            if(xkey == XK_Down) i->setkey(KEY_DOWN, val);
            if(xkey == XK_S) i->setkey(KEY_SELECT, val);
            if(xkey == XK_Print) i->setkey(KEY_PRINT, val);
            if(xkey == XK_Execute) i->setkey(KEY_EXECUT, val);
            if(xkey == XK_S) i->setkey(KEY_SNAPSHOT, val);
            if(xkey == XK_Insert) i->setkey(KEY_INSERT, val);
            if(xkey == XK_Delete) i->setkey(KEY_DELETE, val);
            if(xkey == XK_Help) i->setkey(KEY_HELP, val);
            if(xkey == XK_0) i->setkey(KEY_KEY_0, val);
            if(xkey == XK_1) i->setkey(KEY_KEY_1, val);
            if(xkey == XK_2) i->setkey(KEY_KEY_2, val);
            if(xkey == XK_3) i->setkey(KEY_KEY_3, val);
            if(xkey == XK_4) i->setkey(KEY_KEY_4, val);
            if(xkey == XK_5) i->setkey(KEY_KEY_5, val);
            if(xkey == XK_6) i->setkey(KEY_KEY_6, val);
            if(xkey == XK_7) i->setkey(KEY_KEY_7, val);
            if(xkey == XK_8) i->setkey(KEY_KEY_8, val);
            if(xkey == XK_9) i->setkey(KEY_KEY_9, val);
            if(xkey == XK_a) i->setkey(KEY_KEY_A, val);
            if(xkey == XK_b) i->setkey(KEY_KEY_B, val);
            if(xkey == XK_c) i->setkey(KEY_KEY_C, val);
            if(xkey == XK_d) i->setkey(KEY_KEY_D, val);
            if(xkey == XK_e) i->setkey(KEY_KEY_E, val);
            if(xkey == XK_f) i->setkey(KEY_KEY_F, val);
            if(xkey == XK_g) i->setkey(KEY_KEY_G, val);
            if(xkey == XK_h) i->setkey(KEY_KEY_H, val);
            if(xkey == XK_i) i->setkey(KEY_KEY_I, val);
            if(xkey == XK_j) i->setkey(KEY_KEY_J, val);
            if(xkey == XK_k) i->setkey(KEY_KEY_K, val);
            if(xkey == XK_l) i->setkey(KEY_KEY_L, val);
            if(xkey == XK_m) i->setkey(KEY_KEY_M, val);
            if(xkey == XK_n) i->setkey(KEY_KEY_N, val);
            if(xkey == XK_o) i->setkey(KEY_KEY_O, val);
            if(xkey == XK_p) i->setkey(KEY_KEY_P, val);
            if(xkey == XK_q) i->setkey(KEY_KEY_Q, val);
            if(xkey == XK_r) i->setkey(KEY_KEY_R, val);
            if(xkey == XK_s) i->setkey(KEY_KEY_S, val);
            if(xkey == XK_t) i->setkey(KEY_KEY_T, val);
            if(xkey == XK_u) i->setkey(KEY_KEY_U, val);
            if(xkey == XK_v) i->setkey(KEY_KEY_V, val);
            if(xkey == XK_w) i->setkey(KEY_KEY_W, val);
            if(xkey == XK_x) i->setkey(KEY_KEY_X, val);
            if(xkey == XK_y) i->setkey(KEY_KEY_Y, val);
            if(xkey == XK_z) i->setkey(KEY_KEY_Z, val);
            if(xkey == XK_Super_L) i->setkey(KEY_LWIN, val);
            if(xkey == XK_Super_R) i->setkey(KEY_RWIN, val);
//                if(xkey == XK_Apps) i->setkey(KEY_APPS, val);
//                if(xkey == XK_Sleep) i->setkey(KEY_SLEEP, val);
            if(xkey == XK_KP_0) i->setkey(KEY_NUMPAD0, val);
            if(xkey == XK_KP_1) i->setkey(KEY_NUMPAD1, val);
            if(xkey == XK_KP_2) i->setkey(KEY_NUMPAD2, val);
            if(xkey == XK_KP_3) i->setkey(KEY_NUMPAD3, val);
            if(xkey == XK_KP_4) i->setkey(KEY_NUMPAD4, val);
            if(xkey == XK_KP_5) i->setkey(KEY_NUMPAD5, val);
            if(xkey == XK_KP_6) i->setkey(KEY_NUMPAD6, val);
            if(xkey == XK_KP_7) i->setkey(KEY_NUMPAD7, val);
            if(xkey == XK_KP_8) i->setkey(KEY_NUMPAD8, val);
            if(xkey == XK_KP_9) i->setkey(KEY_NUMPAD9, val);
            if(xkey == XK_Multi_key) i->setkey(KEY_MULTIPLY, val);
            if(xkey == XK_KP_Add) i->setkey(KEY_ADD, val);
            if(xkey == XK_KP_Separator) i->setkey(KEY_SEPARATOR, val);
            if(xkey == XK_KP_Subtract) i->setkey(KEY_SUBTRACT, val);
            if(xkey == XK_KP_Decimal) i->setkey(KEY_DECIMAL, val);
            if(xkey == XK_KP_Divide) i->setkey(KEY_DIVIDE, val);
            if(xkey == XK_F1) i->setkey(KEY_F1, val);
            if(xkey == XK_F2) i->setkey(KEY_F2, val);
            if(xkey == XK_F3) i->setkey(KEY_F3, val);
            if(xkey == XK_F4) i->setkey(KEY_F4, val);
            if(xkey == XK_F5) i->setkey(KEY_F5, val);
            if(xkey == XK_F6) i->setkey(KEY_F6, val);
            if(xkey == XK_F7) i->setkey(KEY_F7, val);
            if(xkey == XK_F8) i->setkey(KEY_F8, val);
            if(xkey == XK_F9) i->setkey(KEY_F9, val);
            if(xkey == XK_F10) i->setkey(KEY_F10, val);
            if(xkey == XK_F11) i->setkey(KEY_F11, val);
            if(xkey == XK_F12) i->setkey(KEY_F12, val);
            if(xkey == XK_F13) i->setkey(KEY_F13, val);
            if(xkey == XK_F14) i->setkey(KEY_F14, val);
            if(xkey == XK_F15) i->setkey(KEY_F15, val);
            if(xkey == XK_F16) i->setkey(KEY_F16, val);
            if(xkey == XK_F17) i->setkey(KEY_F17, val);
            if(xkey == XK_F18) i->setkey(KEY_F18, val);
            if(xkey == XK_F19) i->setkey(KEY_F19, val);
            if(xkey == XK_F20) i->setkey(KEY_F20, val);
            if(xkey == XK_F21) i->setkey(KEY_F21, val);
            if(xkey == XK_F22) i->setkey(KEY_F22, val);
            if(xkey == XK_F23) i->setkey(KEY_F23, val);
            if(xkey == XK_F24) i->setkey(KEY_F24, val);
            if(xkey == XK_Num_Lock) i->setkey(KEY_NUMLOCK, val);
            if(xkey == XK_Scroll_Lock) i->setkey(KEY_SCROLL, val);
            if(xkey == XK_Shift_L) i->setkey(KEY_LSHIFT, val);
            if(xkey == XK_Shift_R) i->setkey(KEY_RSHIFT, val);
            if(xkey == XK_Control_L) i->setkey(KEY_LCONTROL, val);
            if(xkey == XK_Control_R) i->setkey(KEY_RCONTROL, val);
            if(xkey == XK_Meta_L) i->setkey(KEY_LMENU, val);
            if(xkey == XK_Meta_R) i->setkey(KEY_RMENU, val);
            if(xkey == XK_plus) i->setkey(KEY_PLUS, val);
            if(xkey == XK_comma) i->setkey(KEY_COMMA, val);
            if(xkey == XK_minus) i->setkey(KEY_MINUS, val);
            if(xkey == XK_period) i->setkey(KEY_PERIOD, val);
//                if(xkey == XK_3270_Attn) i->setkey(KEY_ATTN, val);
            if(xkey == XK_C) i->setkey(KEY_CRSEL, val);
            if(xkey == XK_E) i->setkey(KEY_EXSEL, val);
            if(xkey == XK_E) i->setkey(KEY_EREOF, val);
            if(xkey == XK_P) i->setkey(KEY_PLAY, val);
            if(xkey == XK_Z) i->setkey(KEY_ZOOM, val);
            if(xkey == XK_Page_Up) i->setkey(KEY_PA1, val);
            if(xkey == XK_Clear) i->setkey(KEY_OEM_CLEAR, val);
        }
    }
}
#endif
