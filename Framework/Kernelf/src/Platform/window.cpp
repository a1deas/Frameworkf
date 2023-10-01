#include "Core/log.h"
#include "window.h"
#include "GLFW/glfw3.h"
#include "EventSystem/mouseEvent.h"
#include "EventSystem/keyboardEvent.h"
#include "EventSystem/windowEvent.h"
#include "input.h"

namespace Ff
{
    Window::Window(int width, int height, const std::string& windowName)
        : m_width(width)
        , m_height(height)
        , m_windowName(windowName)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifndef NDEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

        setFunctionCallback([](const Event& event) {
            //FFINFO("{}: Triggered: {}", event.getEventStr(), event.eventFormat());
        });

        m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), nullptr, nullptr);

        if (m_window == nullptr)
        {
            FFABORT("Failed to create GLFW window");
        }
        FFINFO("Created window");

        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, this);

        glfwSetCursorPosCallback(m_window, mouseMovedCallback);
        glfwSetCursorEnterCallback(m_window, cursorCallback);

        glfwSetScrollCallback(m_window, mouseScrolledCallback);
        glfwSetMouseButtonCallback(m_window, mouseButtonCallback);

        glfwSetKeyCallback(m_window, keyCallback);
        glfwSetCharCallback(m_window, characterCallback);

        glfwSetWindowSizeCallback(m_window, windowResizeCallback);
        glfwSetWindowCloseCallback(m_window, windowCloseCallback);
        glfwSetWindowPosCallback(m_window, windowPositionCallback);
        glfwSetWindowFocusCallback(m_window, windowFocusCallback);
        glfwSetWindowIconifyCallback(m_window, windowIconifyCallback);
        glfwSetWindowMaximizeCallback(m_window, windowMaximizeCallback);
    }

    Window::~Window()
    {
        FFINFO("Destroyed window");
        glfwDestroyWindow(m_window);
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }

    void Window::mouseMovedCallback(GLFWwindow* window, double x, double y)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        Input::setCursorPosition(glm::vec2((float)x, (float)y));
        MouseMovedEvent event(x, y);
        handle.functionCallback(event);
    }

    void Window::mouseScrolledCallback(GLFWwindow* window, double x, double y)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event(y);
        handle.functionCallback(event);
    }

    void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
    {
        if (button == -1)
        {
            return;
        }

        auto& handle = *(Window*)glfwGetWindowUserPointer(window);

        if (action == GLFW_PRESS)
        {
            MouseButtonPressed event(static_cast<MouseButton>(button));
            Input::setButtonState(static_cast<MouseButton>(button), true);
            handle.functionCallback(event);
        }
        else
        {
            MouseButtonReleased event(static_cast<MouseButton>(button));
            Input::setButtonState(static_cast<MouseButton>(button), false);
            handle.functionCallback(event);
        }
    }

    void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_UNKNOWN)
        {
            return;
        }

        auto& handle = *(Window*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(static_cast<Key>(key));
                Input::setKeyState(static_cast<Key>(key), true);
                handle.functionCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(static_cast<Key>(key));
                Input::setKeyState(static_cast<Key>(key), false);
                handle.functionCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyRepeatedEvent event(static_cast<Key>(key));
                handle.functionCallback(event);
                break;
            }
        }
    }

    void Window::characterCallback(GLFWwindow* window, unsigned int codepoint)
    {
        auto&          handle = *(Window*)glfwGetWindowUserPointer(window);
        TextInputEvent event(codepoint);
        handle.functionCallback(event);
    }

    void Window::windowResizeCallback(GLFWwindow* window, int new_width, int new_height)
    {
        auto&              handle = *(Window*)glfwGetWindowUserPointer(window);
        WindowResizedEvent event(new_width, new_height);
        handle.m_width  = new_width;
        handle.m_height = new_height;
        handle.functionCallback(event);
    }

    void Window::windowCloseCallback(GLFWwindow* window)
    {
        auto&            handle = *(Window*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        handle.functionCallback(event);
    }

    void Window::windowPositionCallback(GLFWwindow* window, int xpos, int ypos)
    {
        auto&               handle = *(Window*)glfwGetWindowUserPointer(window);
        WindowPositionEvent event(xpos, ypos);
        handle.functionCallback(event);
    }

    void Window::windowFocusCallback(GLFWwindow* window, int focused)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        if (focused)
        {
            handle.functionCallback(WindowFocusEvent());
        }
        else
        {
            handle.functionCallback(WindowUnfocusEvent());
        }
    }

    void Window::windowIconifyCallback(GLFWwindow* window, int iconified)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        if (iconified)
        {
            handle.functionCallback(WindowIconifyEvent());
        }
        else
        {
            handle.functionCallback(WindowRestoredEvent());
        }
    }

    void Window::windowMaximizeCallback(GLFWwindow* window, int maximized)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        if (maximized)
        {
            handle.functionCallback(WindowMaximizeEvent());
        }
        else
        {
            handle.functionCallback(WindowRestoredEvent());
        }
    }

    void Window::cursorCallback(GLFWwindow* window, int entered)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        if (entered)
        {
            handle.functionCallback(CursorEnterEvent());
        }
        else
        {
            handle.functionCallback(CursorLeftEvent());
        }
    }

} // namespace Ff