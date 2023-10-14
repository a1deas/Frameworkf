#include "timers.h"
#include "GLFW/glfw3.h"

namespace Ff
{

    void Timer::start()
    {
        startTime = glfwGetTime();
    }

    void Timer::end()
    {
        double endTime = glfwGetTime();
        deltaTime = endTime - startTime;
    }

} // namespace Ff