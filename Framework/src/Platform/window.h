#pragma once

#include <string>
#include <functional>

#include "EventSystem/event.h"
#include "GLFW/glfw3.h"

namespace Ff
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& windowName);
        ~Window();

        bool shouldClose() const;

        void swapBuffers();

        void setFunctionCallback(const std::function<void(const Event&)>& function) { functionCallback = function; }
        
    private:
        static void mouseMovedCallback(GLFWwindow* window, double x, double y);
        static void cursorCallback(GLFWwindow* window, int entered);

        static void mouseScrolledCallback(GLFWwindow* window, double x, double y);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void characterCallback(GLFWwindow* window, unsigned int codepoint);

        static void windowResizeCallback(GLFWwindow* window, int width, int height);
        static void windowCloseCallback(GLFWwindow* window);
        static void windowPositionCallback(GLFWwindow* window, int xpos, int ypos);
        static void windowFocusCallback(GLFWwindow* window, int focused);
        static void windowIconifyCallback(GLFWwindow* window, int iconified);
        static void windowMaximizeCallback(GLFWwindow* window, int maximized);


    private:
        GLFWwindow*                       m_window;
        int                               m_width;
        int                               m_height;
        std::string                       m_windowName;
        std::function<void(const Event&)> functionCallback;
    };
} // namespace Ff