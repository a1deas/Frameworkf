#include "platform.h"
#include "GLFW/glfw3.h"
#include "Core/log.h"

namespace Ff
{
	Platform* Platform::Singleton;

	Platform::Platform()
	{
		if (glfwInit())
		{
			FFINFO("GLFW initialised");
		}
		else
		{
			FFERROR("Failed glfw init");
			abort();
		}
		
		Singleton = this;
	}

	Platform::~Platform()
	{
		glfwTerminate();
	}

	void Platform::pollEvents() const
	{
		glfwPollEvents();
	}

}