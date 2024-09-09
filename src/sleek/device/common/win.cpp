#include "win.h"
#if defined win_device_support

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace sleek
{
    namespace device
    {
        Device_win::Device_win(const Device_stub &a) : Device(a)
        {
            gl[0] = gl[1] = gl[2] = gl[3] = 0;
            running = true;
                wc.style = CS_OWNDC;
                wc.lpfnWndProc = WndProc;
                wc.cbClsExtra = 0;
                wc.cbWndExtra = 0;
                wc.hInstance = 0;
                wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
                wc.hCursor = LoadCursor( NULL, IDC_ARROW );
                wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
                wc.lpszMenuName = NULL;
                wc.lpszClassName = "Sleekthink";
            RegisterClass( &wc );

            screen = CreateWindow("Sleekthink", a.name.c_str(), WS_CAPTION | WS_SYSMENU | WS_VISIBLE, 0, 0, a.size.width, a.size.height, NULL, NULL, 0, NULL );
            dc = GetDC(screen);
                ZeroMemory( &pfd, sizeof( pfd ) );
                pfd.nSize = sizeof( pfd );
                pfd.nVersion = 1;
                pfd.dwFlags = PFD_DRAW_TO_WINDOW | (PFD_SUPPORT_OPENGL*(a.ctw == RCTX_OGL) | PFD_DOUBLEBUFFER);
                pfd.iPixelType = PFD_TYPE_RGBA;
                pfd.cColorBits = a.bits;
                pfd.cDepthBits = 16;
                pfd.iLayerType = PFD_MAIN_PLANE;
                int format = ChoosePixelFormat(dc, &pfd);
                SetPixelFormat(dc, format, &pfd);
            makeRenderContext(GRC_0);
            switchToRenderContext(GRC_0);
            setVideoSize(a.size);
            enableWindowDecorator(info.decorator);

            initOpenCL();
            welcomeMessage();
            testGlError();

            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        }

        Device_win::~Device_win()
        {
            ReleaseDC(screen, dc);
            DestroyWindow(screen);
        }

        void Device_win::setCaption(const std::string &name)
        {
            SetWindowText(screen, name.c_str());
            Device::setCaption(name);
        }

        void Device_win::setVideoSize(const math::vec2i &i)
        {
            Device::setVideoSize(i);
            ShowWindow(screen, SW_SHOW);
            UpdateWindow(screen);
            MoveWindow(screen, (GetSystemMetrics(SM_CXSCREEN)-i.width)/2, (GetSystemMetrics(SM_CYSCREEN)-i.height)/2, i.width, i.height, FALSE);
        }

        void Device_win::setWindowPos(const math::vec2i &i)
        {
            ShowWindow(screen, SW_SHOW);
            UpdateWindow(screen);
            MoveWindow(screen, i.width, i.height, info.size.width, info.size.height, FALSE);
            Device::setVideoSize(i);
        }

        math::vec2i Device_win::getDesktopVideoSize() const
        {
            return math::vec2i(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
        }

        void Device_win::enableWindowDecorator(bool flag)
        {
            Device::enableWindowDecorator(flag);
            SetWindowLong(screen, GWL_STYLE, flag ? WS_CAPTION | WS_SYSMENU | WS_VISIBLE : WS_DLGFRAME);
            ShowWindow(screen, SW_SHOW);
            UpdateWindow(screen);
            SetWindowPos(screen, 0,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
        }

        void Device_win::setGamma(const math::pixel &c)
        {
			HDC hDC = GetDC(NULL); // Get the device context for the entire desktop
			if (hDC)
			{
				// Set the gamma ramp for each color component
				SetDeviceGammaRamp(hDC, &c.ptr);
				ReleaseDC(NULL, hDC);
			}
        }

        void Device_win::setFullScreen(bool f)
        {
			static RECT windowRect;
			static bool isFullScreen = false;

			if (f && !isFullScreen)
			{
				// Store the current window position and size
				GetWindowRect(screen, &windowRect);

				// Set the window style to remove the caption and border
				SetWindowLongPtr(screen, GWL_STYLE, WS_OVERLAPPEDWINDOW & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU));

				// Move the window to cover the entire desktop
				SetWindowPos(screen, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);

				isFullScreen = true;
			}
			else if (!f && isFullScreen)
			{
				// Restore the window style and position
				SetWindowLongPtr(screen, GWL_STYLE, WS_OVERLAPPEDWINDOW);
				SetWindowPos(screen, HWND_TOP, windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_FRAMECHANGED);

				isFullScreen = false;
			}
        }

        bool Device_win::run()
        {
            MSG msg;
            while(PeekMessage(&msg,screen,0,0,PM_NOREMOVE) && running)
            {
                if(!GetMessage(&msg,screen,0,0)) running = false;//current->exit_msg = true;
                DispatchMessage(&msg);
            }
            return Device::run();
        }

        void Device_win::begin(const math::pixel &color)
        {
            Device::begin(color);
        }

        void Device_win::exit()
        {
            PostQuitMessage(0);
            Device::exit();
        }

        bool Device_win::manage()
        {
        }

        void Device_win::end()
        {
            Device::end();
        }
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
        case WM_CREATE: return 0;
        case WM_CLOSE: PostQuitMessage( 0 ); return 0;
        case WM_DESTROY: PostQuitMessage( 0 ); return 0;
        case WM_KEYDOWN: if( wParam == VK_ESCAPE) PostQuitMessage(0); return 0;
        default: return DefWindowProc( hWnd, message, wParam, lParam );
	}
}

#endif
