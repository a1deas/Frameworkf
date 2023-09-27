#include "glad/glad.h"
#include "graphicsContextOGL.h"


namespace Ff
{
    Ff::GraphicsContextOGL::GraphicsContextOGL(Window* window)
        : GraphicsContext(window)
    {
        glfwMakeContextCurrent(window->getWindow());

        if (!gladLoadGL())
        {
            FFABORT("OpenGL initialize failed!");
        }
    }

} // namespace Ff