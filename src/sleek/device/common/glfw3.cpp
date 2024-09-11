#include "glfw3.h"

#ifdef glfw3_device_support

void glfw3_error_callback(int error, const char* description)
{
    fprintf(stderr, "Device_glfw3 Error: %s\n", description);
}

//https://github.com/glfw/glfw/issues/1699
bool glfw_get_mouse_monitor(
    GLFWmonitor** monitor,
    GLFWwindow* window
) {
    bool success = false;

    double cursor_position[2] = {0};
    glfwGetCursorPos(window, &cursor_position[0], &cursor_position[1]);

    int window_position[2] = {0};
    glfwGetWindowPos(window, &window_position[0], &window_position[1]);

    int monitors_size = 0;
    GLFWmonitor** monitors = glfwGetMonitors(&monitors_size);

    // convert cursor position from window coordinates to screen coordinates
    cursor_position[0] += window_position[0];
    cursor_position[1] += window_position[1];

    for (int i = 0; ((!success) && (i < monitors_size)); ++i)
    {
        int monitor_position[2] = {0};
        glfwGetMonitorPos(monitors[i], &monitor_position[0], &monitor_position[1]);

        const GLFWvidmode* monitor_video_mode = glfwGetVideoMode(monitors[i]);

        if (
            (cursor_position[0] < monitor_position[0]) ||
            (cursor_position[0] > (monitor_position[0] + monitor_video_mode->width)) ||
            (cursor_position[1] < monitor_position[1]) ||
            (cursor_position[1] > (monitor_position[1] + monitor_video_mode->height))
        ) {
            *monitor = monitors[i];
            success = true;
        }
    }

    // true: monitor contains the monitor the mouse is on
    // false: monitor is unmodified
    return success;
}

namespace sleek
{
    namespace device
    {
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            auto user = glfwGetWindowUserPointer(window);
            auto win = static_cast<sleek::device::Device_glfw3*>(user);
            auto evt = win->getEventReceiver();
            auto i = win->getCurrentEvent();

            bool val = false;

            if(action == GLFW_PRESS)
            {
                val = true;
                i->type = EVENT_KEY_DOWN;
            }
            else if (action == GLFW_RELEASE)
                i->type = EVENT_KEY_UP;
            else
                return;

            /** key event **/
            if(key == GLFW_KEY_TAB) i->setkey(KEY_TAB, val);
            if(key == GLFW_KEY_ENTER) i->setkey(KEY_RETURN, val);
            if(key == GLFW_KEY_RIGHT_SHIFT || key == GLFW_KEY_LEFT_SHIFT) i->setkey(KEY_SHIFT, val);
            if(key == GLFW_KEY_RIGHT_CONTROL || key == GLFW_KEY_LEFT_CONTROL) i->setkey(KEY_CONTROL, val);
            if(key == GLFW_KEY_MENU) i->setkey(KEY_MENU, val);
            if(key == GLFW_KEY_PAUSE) i->setkey(KEY_PAUSE, val);
            if(key == GLFW_KEY_ESCAPE) i->setkey(KEY_ESCAPE, val);
            if(key == GLFW_KEY_SPACE) i->setkey(KEY_SPACE, val);
            if(key == GLFW_KEY_END) i->setkey(KEY_END, val);
            if(key == GLFW_KEY_HOME) i->setkey(KEY_HOME, val);
            if(key == GLFW_KEY_LEFT) i->setkey(KEY_LEFT, val);
            if(key == GLFW_KEY_UP) i->setkey(KEY_UP, val);
            if(key == GLFW_KEY_RIGHT) i->setkey(KEY_RIGHT, val);
            if(key == GLFW_KEY_DOWN) i->setkey(KEY_DOWN, val);
            if(key == GLFW_KEY_INSERT) i->setkey(KEY_INSERT, val);
            if(key == GLFW_KEY_DELETE) i->setkey(KEY_DELETE, val);
            if(key == GLFW_KEY_0) i->setkey(KEY_KEY_0, val);
            if(key == GLFW_KEY_1) i->setkey(KEY_KEY_1, val);
            if(key == GLFW_KEY_2) i->setkey(KEY_KEY_2, val);
            if(key == GLFW_KEY_3) i->setkey(KEY_KEY_3, val);
            if(key == GLFW_KEY_4) i->setkey(KEY_KEY_4, val);
            if(key == GLFW_KEY_5) i->setkey(KEY_KEY_5, val);
            if(key == GLFW_KEY_6) i->setkey(KEY_KEY_6, val);
            if(key == GLFW_KEY_7) i->setkey(KEY_KEY_7, val);
            if(key == GLFW_KEY_8) i->setkey(KEY_KEY_8, val);
            if(key == GLFW_KEY_9) i->setkey(KEY_KEY_9, val);
            if(key == GLFW_KEY_KP_0) i->setkey(KEY_NUMPAD0, val);
            if(key == GLFW_KEY_KP_1) i->setkey(KEY_NUMPAD1, val);
            if(key == GLFW_KEY_KP_2) i->setkey(KEY_NUMPAD2, val);
            if(key == GLFW_KEY_KP_3) i->setkey(KEY_NUMPAD3, val);
            if(key == GLFW_KEY_KP_4) i->setkey(KEY_NUMPAD4, val);
            if(key == GLFW_KEY_KP_5) i->setkey(KEY_NUMPAD5, val);
            if(key == GLFW_KEY_KP_6) i->setkey(KEY_NUMPAD6, val);
            if(key == GLFW_KEY_KP_7) i->setkey(KEY_NUMPAD7, val);
            if(key == GLFW_KEY_KP_8) i->setkey(KEY_NUMPAD8, val);
            if(key == GLFW_KEY_KP_9) i->setkey(KEY_NUMPAD9, val);
            if(key == GLFW_KEY_A) i->setkey(KEY_KEY_A, val);
            if(key == GLFW_KEY_B) i->setkey(KEY_KEY_B, val);
            if(key == GLFW_KEY_C) i->setkey(KEY_KEY_C, val);
            if(key == GLFW_KEY_D) i->setkey(KEY_KEY_D, val);
            if(key == GLFW_KEY_E) i->setkey(KEY_KEY_E, val);
            if(key == GLFW_KEY_F) i->setkey(KEY_KEY_F, val);
            if(key == GLFW_KEY_G) i->setkey(KEY_KEY_G, val);
            if(key == GLFW_KEY_H) i->setkey(KEY_KEY_H, val);
            if(key == GLFW_KEY_I) i->setkey(KEY_KEY_I, val);
            if(key == GLFW_KEY_J) i->setkey(KEY_KEY_J, val);
            if(key == GLFW_KEY_K) i->setkey(KEY_KEY_K, val);
            if(key == GLFW_KEY_L) i->setkey(KEY_KEY_L, val);
            if(key == GLFW_KEY_M) i->setkey(KEY_KEY_M, val);
            if(key == GLFW_KEY_N) i->setkey(KEY_KEY_N, val);
            if(key == GLFW_KEY_O) i->setkey(KEY_KEY_O, val);
            if(key == GLFW_KEY_P) i->setkey(KEY_KEY_P, val);
            if(key == GLFW_KEY_Q) i->setkey(KEY_KEY_Q, val);
            if(key == GLFW_KEY_R) i->setkey(KEY_KEY_R, val);
            if(key == GLFW_KEY_S) i->setkey(KEY_KEY_S, val);
            if(key == GLFW_KEY_T) i->setkey(KEY_KEY_T, val);
            if(key == GLFW_KEY_U) i->setkey(KEY_KEY_U, val);
            if(key == GLFW_KEY_V) i->setkey(KEY_KEY_V, val);
            if(key == GLFW_KEY_W) i->setkey(KEY_KEY_W, val);
            if(key == GLFW_KEY_X) i->setkey(KEY_KEY_X, val);
            if(key == GLFW_KEY_Y) i->setkey(KEY_KEY_Y, val);
            if(key == GLFW_KEY_Z) i->setkey(KEY_KEY_Z, val);
            if(key == GLFW_KEY_MINUS) i->setkey(KEY_SUBTRACT, val);
            if(key == GLFW_KEY_SLASH) i->setkey(KEY_DIVIDE, val);
            if(key == GLFW_KEY_F1) i->setkey(KEY_F1, val);
            if(key == GLFW_KEY_F2) i->setkey(KEY_F2, val);
            if(key == GLFW_KEY_F3) i->setkey(KEY_F3, val);
            if(key == GLFW_KEY_F4) i->setkey(KEY_F4, val);
            if(key == GLFW_KEY_F5) i->setkey(KEY_F5, val);
            if(key == GLFW_KEY_F6) i->setkey(KEY_F6, val);
            if(key == GLFW_KEY_F7) i->setkey(KEY_F7, val);
            if(key == GLFW_KEY_F8) i->setkey(KEY_F8, val);
            if(key == GLFW_KEY_F9) i->setkey(KEY_F9, val);
            if(key == GLFW_KEY_F10) i->setkey(KEY_F10, val);
            if(key == GLFW_KEY_F11) i->setkey(KEY_F11, val);
            if(key == GLFW_KEY_F12) i->setkey(KEY_F12, val);
            if(key == GLFW_KEY_F13) i->setkey(KEY_F13, val);
            if(key == GLFW_KEY_F14) i->setkey(KEY_F14, val);
            if(key == GLFW_KEY_F15) i->setkey(KEY_F15, val);
            if(key == GLFW_KEY_LEFT_SHIFT) i->setkey(KEY_LSHIFT, val);
            if(key == GLFW_KEY_RIGHT_SHIFT) i->setkey(KEY_RSHIFT, val);
            if(key == GLFW_KEY_LEFT_CONTROL) i->setkey(KEY_LCONTROL, val);
            if(key == GLFW_KEY_RIGHT) i->setkey(KEY_RCONTROL, val);
//            if(key == GLFW_KEY_LMETA) i->setkey(KEY_LMENU, val);
//            if(key == GLFW_KEY_RMETA) i->setkey(KEY_RMENU, val);
//            if(key == GLFW_KEY_PLUS) i->setkey(KEY_PLUS, val);
            if(key == GLFW_KEY_COMMA) i->setkey(KEY_COMMA, val);
            if(key == GLFW_KEY_MINUS) i->setkey(KEY_MINUS, val);
            if(key == GLFW_KEY_PERIOD) i->setkey(KEY_PERIOD, val);
//            if(key == GLFW_KEY_AT) i->setkey(KEY_ATTN, val);
//                if(key == GLFW_KEY_c) i->setkey(KEY_CRSEL, val);
//                if(key == GLFW_KEY_E) i->setkey(KEY_EXSEL, val);
//                if(key == GLFW_KEY_E) i->setkey(KEY_EREOF, val);
//                if(key == GLFW_KEY_P) i->setkey(KEY_PLAY, val);
//                if(key == GLFW_KEY_Z) i->setkey(KEY_ZOOM, val);
//            if(key == GLFW_KEY_PAGEUP) i->setkey(KEY_PA1, val);

            evt->manage(i);
            if(!evt->running())
                win->exit();
            i->clear();
        }

        void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
        {
            auto user = glfwGetWindowUserPointer(window);
            auto win = static_cast<sleek::device::Device_glfw3*>(user);
            auto evt = win->getEventReceiver();
            auto i = win->getCurrentEvent();

            if (action == GLFW_PRESS)
                i->type = EVENT_MOUSSE_DOWN;
            else if (action == GLFW_RELEASE)
                i->type = EVENT_MOUSSE_UP;
            else
                return;
                        
            if(button == GLFW_MOUSE_BUTTON_LEFT)
            {
                i->mouse[MOUSE_LEFT] = true;
                i->setkey(KEY_LBUTTON, true);
            }

            if(button == GLFW_MOUSE_BUTTON_MIDDLE)
            {
                i->mouse[MOUSE_MIDDLE] = true;
                i->setkey(KEY_MBUTTON, true);
            }

            if(button == GLFW_MOUSE_BUTTON_RIGHT)
            {
                i->mouse[MOUSE_RIGHT] = true;
                i->setkey(KEY_RBUTTON, true);
            }

            evt->manage(i);
            if(!evt->running())
                win->exit();
            i->clear();
        }

        void mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset)
        {
            auto user = glfwGetWindowUserPointer(window);
            auto win = static_cast<sleek::device::Device_glfw3*>(user);
            auto evt = win->getEventReceiver();
            auto i = win->getCurrentEvent();

            if(xoffset > 0) { i->mouse[MOUSE_WHEEL_UP] = true;   }
            if(yoffset > 0) { i->mouse[MOUSE_WHEEL_UP] = true;   }
            if(xoffset < 0) { i->mouse[MOUSE_WHEEL_DOWN] = true; }
            if(yoffset < 0) { i->mouse[MOUSE_WHEEL_DOWN] = true; }

            evt->manage(i);
            if(!evt->running())
                win->exit();
            i->clear();
        }

        // Mouse position callback function
        void mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
        {
            auto user = glfwGetWindowUserPointer(window);
            auto win = static_cast<sleek::device::Device_glfw3*>(user);
            auto evt = win->getEventReceiver();
            auto i = win->getCurrentEvent();

            i->type = EVENT_MOUSSE_MOVED;
            i->mouse_pos.x = xpos;
            i->mouse_pos.y = ypos;

            evt->manage(i);
            if(!evt->running())
                win->exit();
            i->clear();
        }

        // Window resize callback function
        void window_resize_callback(GLFWwindow* window, int width, int height)
        {
            auto user = glfwGetWindowUserPointer(window);
            auto win = static_cast<sleek::device::Device_glfw3*>(user);
            auto evt = win->getEventReceiver();
            auto i = win->getCurrentEvent();

            evt->manage(i);
            if(!evt->running())
                win->exit();
            i->clear();
        }

        Device_glfw3::Device_glfw3(const Device_stub &a) noexcept : Device(a)
        {
            if (!glfwInit())
            {
                std::cout << "Device_glfw3 Initialization failed !!\n" << std::endl;
                return;
            }

            glfwSetErrorCallback(glfw3_error_callback);

            // Context profiles are only defined for OpenGL version 3.2 and above
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

            window = glfwCreateWindow(a.size.x, a.size.y, a.name.c_str(), NULL, NULL);

            if (!window)
            {
                std::cout << "Device_glfw3 Window or OpenGL context creation failed !!\n" << std::endl;
                return;
            }

            monitor = glfwGetWindowMonitor(window);
            glfwSetWindowUserPointer(window, this);

            glfwSetKeyCallback(window, key_callback);
            glfwSetScrollCallback(window, mouse_wheel_callback);
            glfwSetMouseButtonCallback(window, mouse_button_callback);
            glfwSetCursorPosCallback(window, mouse_position_callback);
            glfwSetWindowSizeCallback(window, window_resize_callback);
            glfwMakeContextCurrent(window);
            
            running = true;
            welcomeMessage();
        }

        Device_glfw3::~Device_glfw3() noexcept
        {
            glfwDestroyWindow(window);
            glfwTerminate();
        }

        void Device_glfw3::setCaption(const std::string &name) noexcept
        {
            Device::setCaption(name);
            glfwSetWindowTitle(window, name.c_str());
        }

        void Device_glfw3::setVideoSize(const math::vec2i &i) noexcept
        {
            Device::setVideoSize(i);
            glfwSetWindowSize(window, i.x, i.y);
        }

        void Device_glfw3::setWindowPos(const math::vec2i &i) noexcept
        {
            glfwSetWindowPos(window, i.x, i.y);
        }

        void Device_glfw3::enableWindowDecorator(bool z) noexcept
        {
            Device::enableWindowDecorator(z);
        }

        void Device_glfw3::setGamma(const math::pixel &c) noexcept
        {
        }

        void Device_glfw3::setFullScreen(bool f) noexcept
        {
            info.fullscreen = f;
        }

        math::vec2i Device_glfw3::getDesktopVideoSize() const noexcept
        {
            math::vec2i size;
            GLFWmonitor *monitor;
            glfw_get_mouse_monitor(&monitor, window);
            const GLFWvidmode * mode = glfwGetVideoMode(monitor);
            size.x = mode->width;
            size.y = mode->height;
            return size;
        }

        bool Device_glfw3::run() noexcept
        {
            reading = true;
            glfwPollEvents();
            current->exit_msg = glfwWindowShouldClose(window);
            return Device::run();
        }

        void Device_glfw3::begin(const math::pixel &color) noexcept
        {
            if(!reading) return;
            Device::begin();
        }

        bool Device_glfw3::manage() noexcept
        {
            evt->manage(current);
            current->clear();
            running = evt->asRunning;
            return true;
        }

        void Device_glfw3::end() noexcept
        {
            glfwSwapBuffers(window);
            if(!reading) return;
            Device::end();
            reading = false;
        }

        void Device_glfw3::WarpMouse(const math::vec2i &i) noexcept
        {
            glfwSetCursorPos(window, i.x, i.y);
        }

        void Device_glfw3::ShowMouse(bool i) noexcept
        {
            glfwSetInputMode(window, GLFW_CURSOR, i ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
        }
    }
}
#endif