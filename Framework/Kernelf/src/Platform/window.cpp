#include "Core/log.h"
#include "window.h"
#include "GLFW/glfw3.h"
#include "EventSystem/mouseEvent.h"
#include "EventSystem/keyboardEvent.h"
#include "EventSystem/windowEvent.h"
#include "input.h"
#include "Core/profile.h"

namespace Ff
{
    Window::Window(int width, int height, const std::string& windowName)
        : m_Width(width)
        , m_Height(height)
        , m_WindowName(windowName)
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

        m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(), nullptr, nullptr);

        if (m_Window == nullptr)
        {
            FFABORT("Failed to create GLFW window");
        }
        FFINFO("Created window");

        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);

        glfwSetCursorPosCallback(m_Window, mouseMovedCallback);
        glfwSetCursorEnterCallback(m_Window, cursorCallback);

        glfwSetScrollCallback(m_Window, mouseScrolledCallback);
        glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);

        glfwSetKeyCallback(m_Window, keyCallback);
        glfwSetCharCallback(m_Window, characterCallback);

        glfwSetFramebufferSizeCallback(m_Window, windowResizeCallback);
        glfwSetWindowCloseCallback(m_Window, windowCloseCallback);
        glfwSetWindowPosCallback(m_Window, windowPositionCallback);
        glfwSetWindowFocusCallback(m_Window, windowFocusCallback);
        glfwSetWindowIconifyCallback(m_Window, windowIconifyCallback);
        glfwSetWindowMaximizeCallback(m_Window, windowMaximizeCallback);
    }

    Window::~Window()
    {
        FFINFO("Destroyed window");
        glfwDestroyWindow(m_Window);
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::swapBuffers()
    {
        FF_PROFILE_SCOPE();
        glfwSwapBuffers(m_Window);
    }

    void Window::mouseMovedCallback(GLFWwindow* window, double x, double y)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        Input::setCursorPosition(glm::vec2((float)x, (float)y));
        MouseMovedEvent event(x, y);
        handle.m_FunctionCallback(event);
    }

    void Window::mouseScrolledCallback(GLFWwindow* window, double, double y)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        Input::setScrollOffset(y);
        MouseScrolledEvent event(y);
        handle.m_FunctionCallback(event);
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
            handle.m_FunctionCallback(event);
        }
        else
        {
            MouseButtonReleased event(static_cast<MouseButton>(button));
            Input::setButtonState(static_cast<MouseButton>(button), false);
            handle.m_FunctionCallback(event);
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
                handle.m_FunctionCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(static_cast<Key>(key));
                Input::setKeyState(static_cast<Key>(key), false);
                handle.m_FunctionCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyRepeatedEvent event(static_cast<Key>(key));
                handle.m_FunctionCallback(event);
                break;
            }
        }
    }

    void Window::characterCallback(GLFWwindow* window, unsigned int codepoint)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        TextInputEvent event(codepoint);
        handle.m_FunctionCallback(event);
    }

    void Window::windowResizeCallback(GLFWwindow* window, int new_width, int new_height)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        WindowResizedEvent event(new_width, new_height);
        handle.m_Width = new_width;
        handle.m_Height = new_height;
        handle.m_FunctionCallback(event);
    }

    void Window::windowCloseCallback(GLFWwindow* window)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        handle.m_FunctionCallback(event);
    }

    void Window::windowPositionCallback(GLFWwindow* window, int xpos, int ypos)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        WindowPositionEvent event(xpos, ypos);
        handle.m_FunctionCallback(event);
    }

    void Window::windowFocusCallback(GLFWwindow* window, int focused)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        if (focused)
        {
            handle.m_FunctionCallback(WindowFocusEvent());
        }
        else
        {
            handle.m_FunctionCallback(WindowUnfocusEvent());
        }
    }

    void Window::windowIconifyCallback(GLFWwindow* window, int iconified)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        if (iconified)
        {
            handle.m_FunctionCallback(WindowIconifyEvent());
        }
        else
        {
            handle.m_FunctionCallback(WindowRestoredEvent());
        }
    }

    void Window::windowMaximizeCallback(GLFWwindow* window, int maximized)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        if (maximized)
        {
            handle.m_FunctionCallback(WindowMaximizeEvent());
        }
        else
        {
            handle.m_FunctionCallback(WindowRestoredEvent());
        }
    }

    void Window::cursorCallback(GLFWwindow* window, int entered)
    {
        auto& handle = *(Window*)glfwGetWindowUserPointer(window);
        if (entered)
        {
            handle.m_FunctionCallback(CursorEnterEvent());
        }
        else
        {
            handle.m_FunctionCallback(CursorLeftEvent());
        }
    }

} // namespace Ff