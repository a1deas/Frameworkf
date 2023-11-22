#include "Core/log.h"
#include "platform.h"
#include "GLFW/glfw3.h"
#include "Core/profile.h"

namespace Ff
{
    Platform* Platform::s_Singleton;

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

        s_Singleton = this;
    }

    Platform::~Platform()
    {
        glfwTerminate();
    }

    void Platform::pollEvents() const
    {
        FF_PROFILE_SCOPE();
        glfwPollEvents();
    }
} // namespace Ff