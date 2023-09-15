#include "window.h"
#include "GLFW/glfw3.h"
#include "Core/log.h"
#include "EventSystem/mouseEvent.h"
#include "EventSystem/keyboardEvent.h"
#include "EventSystem/windowEvent.h"

namespace Ff
{
	Window::Window(int width, int height, const std::string& windowName)
		: m_width(width)
		, m_height(height)
		, m_windowName(windowName)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		setFunctionCallback([](const Event& event)
			{
				FFINFO("{}: Triggered: {}", event.getEventStr(), event.eventFormat());
			});

		m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), nullptr, nullptr);
		if (m_window == nullptr)
		{
			FFERROR("Failed to create GLFW window");
			abort();
		}
		FFINFO("Created window");
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		
		glfwSetCursorPosCallback(m_window, mouseMovedCallback);
		glfwSetScrollCallback(m_window, mouseScrolledCallback);
		glfwSetMouseButtonCallback(m_window, mouseButtonCallback);

		glfwSetKeyCallback(m_window, keyCallback);

		glfwSetWindowSizeCallback(m_window, windowResizeCallback);
		glfwSetWindowCloseCallback(m_window, windowCloseCallback);
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
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		
		if (action == GLFW_PRESS)
		{
			MouseButtonPressed event(button);
			handle.functionCallback(event);
		}
		else
		{
			MouseButtonReleased event(button);
			handle.functionCallback(event);
		}
	}

	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		
		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(static_cast<Key>(key));
				handle.functionCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(static_cast<Key>(key));
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

	void Window::windowResizeCallback(GLFWwindow* window, int new_width, int new_height)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		WindowResizedEvent event(new_width, new_height);
		handle.m_width = new_width;
		handle.m_height = new_height;
		handle.functionCallback(event);
	}

	void Window::windowCloseCallback(GLFWwindow* window)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		handle.functionCallback(event);
	}

}