#include "graphicsContextOGL.h"
#include "glad/glad.h"
#include "shaderProgramOGL.h"

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

    void GraphicsContextOGL::useProgram(std::shared_ptr<ShaderProgram> program)
    {
        std::shared_ptr<ShaderProgramOGL> glProgram = std::static_pointer_cast<ShaderProgramOGL>(program);
        glUseProgram(glProgram->getId());
    }

} // namespace Ff