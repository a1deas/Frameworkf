#include "Core/log.h"
#include "platform.h"
#include "GLFW/glfw3.h"

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

} // namespace Ff