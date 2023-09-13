#include "window.h"
#include "GLFW/glfw3.h"
#include "Core/log.h"
#include "EventSystem/mouseEvent.h"

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

		setFunctionCallback([](Event& event)
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
		// *
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

}