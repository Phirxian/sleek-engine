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
        Device_glfw3::Device_glfw3(const Device_stub &a) noexcept : Device(a)
        {
            if (!glfwInit())
            {
                std::cout << "Device_glfw3 Initialization failed !!\n" << std::endl;
                return;
            }

            glfwSetErrorCallback(glfw3_error_callback);

            // Context profiles are only defined for OpenGL version 3.2 and above
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = glfwCreateWindow(a.size.x, a.size.y, a.name.c_str(), NULL, NULL);
            monitor = glfwGetWindowMonitor(window);
            //monitor = glfwGetPrimaryMonitor();
            glfwSetWindowUserPointer(window, this);

            if (!window)
            {
                std::cout << "Device_glfw3 Window or OpenGL context creation failed !!\n" << std::endl;
                return;
            }

            // glfwSetWindowSizeCallback
            // glfwSetKeyCallback(window, key_callback);
            glfwMakeContextCurrent(window);
            
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