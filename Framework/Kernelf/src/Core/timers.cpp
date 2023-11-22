#include "timers.h"
#include "GLFW/glfw3.h"

namespace Ff
{

    void Timer::start()
    {
        m_StartTime = glfwGetTime();
    }

    void Timer::end()
    {
        double endTime = glfwGetTime();
        m_DeltaTime = endTime - m_StartTime;
    }

} // namespace Ff