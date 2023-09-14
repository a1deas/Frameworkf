#pragma once

#include "GLFW/glfw3.h"
#include "EventSystem/event.h"

#include <string>
#include <functional>

namespace Ff
{
	class Window
	{
	public:
		Window(int width, int height, const std::string& windowName);
		~Window();

		bool shouldClose() const;

		void swapBuffers();
	
		static void mouseMovedCallback(GLFWwindow* window, double x, double y);
		static void mouseScrolledCallback(GLFWwindow* window, double x, double y);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);



		void setFunctionCallback(const std::function<void(Event&)>& function) { functionCallback = function; }
	private:
		GLFWwindow* m_window;
		int m_width;
		int m_height;
		std::string m_windowName;
		std::function<void(Event&)> functionCallback;
	};
}