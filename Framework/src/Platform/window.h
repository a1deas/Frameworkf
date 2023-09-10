#pragma once

#include "GLFW/glfw3.h"
#include <string>

namespace Ff
{
	class Window
	{
	public:
		Window(int width, int height, const std::string& windowName);
		~Window();

		bool shouldClose() const;

		void swapBuffers();
	
	private:
		GLFWwindow* m_window;
		int m_width;
		int m_height;
		std::string m_windowName;
	};
}