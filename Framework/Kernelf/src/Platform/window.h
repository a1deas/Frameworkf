#pragma once

#include <string>
#include <functional>

#include "EventSystem/event.h"
#include "GLFW/glfw3.h"

namespace Ff
{
    /**
     * Window class, that represents window's definition and properties, 
     * and stores an instance of window, and window events callbacks.
     */
    class Window
    {
    public:
        /**
         * Create window.
         * @param width window's width.
         * @param height window's height.
         * @param windowName window's title.
         */
        Window(int width, int height, const std::string& windowName);
        ~Window();

        /** Checks if window should close. */
        bool shouldClose() const;

        /** Swaps buffer(front or back), while drawing into another. */
        void swapBuffers();

        /** Sets function callback to receive platform events. */
        void setFunctionCallback(const std::function<void(const Event&)>& function) { m_FunctionCallback = function; }
        
        /** Get window. */
        GLFWwindow* getWindow() const { return m_Window; }

        /** Get window's width. */
        int getWidth() const { return m_Width; }
        /** Get window's height.  */
        int getHeight() const { return m_Height; }

    private:
        /** If mouse moved handles [MouseMovedEvent] and sets cursor position to x/y. */
        static void mouseMovedCallback(GLFWwindow* window, double x, double y);
        /** If cursor enter or leave window area, handles [CursorEnteredEvent]/[CursorLeftEvent]. */
        static void cursorCallback(GLFWwindow* window, int entered);

        /** If mouse scrolled, handles [MouseScrolledEvent] and sets scroll offset to y. */
        static void mouseScrolledCallback(GLFWwindow* window, double x, double y);
        /** If any mouse button is pressed, handles [MouseButtonPressedEvent]/[MouseButtonReleasedEvent] and stores button and its state(pressed/released). */
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);

        /** If any key button is pressed, handles [KeyPressedEvent],[KeyReleasedEvent],[KeyRepeatedEvent], stores key and its state(pressed/released/repeated)*/
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        /** If any character is typed, handles [TextInputEvent]. */
        static void characterCallback(GLFWwindow* window, unsigned int codepoint);

        /** If window gets resized, handles [WindowResizedEvent] and stores its new width and height. */
        static void windowResizeCallback(GLFWwindow* window, int width, int height);
        /** If window gets closed, handles [WindowClosedEvent]. */
        static void windowCloseCallback(GLFWwindow* window);
        /** If window changes its position, handles [WindowPositionEvent], and stores its current position. */
        static void windowPositionCallback(GLFWwindow* window, int xpos, int ypos);
        /** If window gets focused/unfocused, handles [WindowFocusEvent]/[WindowUnfocusEvent]. */
        static void windowFocusCallback(GLFWwindow* window, int focused);
        /** If window gets iconified/restored, handles [WindowIconifyEvent]/[WindowRestoredEvent]. */
        static void windowIconifyCallback(GLFWwindow* window, int iconified);
        /** If window gets maximized/restored, handles [WindowMaximizeEvent]/[WindowRestoredEvent]. */
        static void windowMaximizeCallback(GLFWwindow* window, int maximized);

    private:
        GLFWwindow*                       m_Window;
        int                               m_Width;
        int                               m_Height;
        std::string                       m_WindowName;
        std::function<void(const Event&)> m_FunctionCallback;
    };
} // namespace Ff