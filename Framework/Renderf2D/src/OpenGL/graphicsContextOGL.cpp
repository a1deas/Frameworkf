#include "graphicsContextOGL.h"
#include "glad/glad.h"
#include "shaderProgramOGL.h"
#include "vertexBufferOGL.h"

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

    void GraphicsContextOGL::bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
    {
        std::shared_ptr<VertexBufferOGL> vertexBuffer = std::static_pointer_cast<VertexBufferOGL>(buffer);
        glBindVertexArray(vertexBuffer->getVertexArray());
    }

    void GraphicsContextOGL::draw(uint32_t vertexCount)
    {
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

    void GraphicsContextOGL::setViewport(Viewport2D viewport)
    {
        glViewport((int)viewport.x, (int)viewport.y, (int)viewport.width, (int)viewport.height);
    }

} // namespace Ff