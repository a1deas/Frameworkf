#include "glad/glad.h"
#include "graphicsContextOGL.h"
#include "shaderProgramOGL.h"
#include "vertexBufferOGL.h"
#include "indexBufferOGL.h"
#include "glm/gtc/type_ptr.hpp"

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
        boundProgram_ = glProgram;
    }

    void GraphicsContextOGL::bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
    {
        std::shared_ptr<VertexBufferOGL> vertexBuffer = std::static_pointer_cast<VertexBufferOGL>(buffer);
        glBindVertexArray(vertexBuffer->getVertexArray());
    }

    void GraphicsContextOGL::bindIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
    {
        std::shared_ptr<IndexBufferOGL> indexBuffer = std::static_pointer_cast<IndexBufferOGL>(buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getBuffer());
    }

    void GraphicsContextOGL::draw(uint32_t vertexCount)
    {
        glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr);
    }

    void GraphicsContextOGL::setViewport(Viewport2D viewport)
    {
        glViewport((int)viewport.x, (int)viewport.y, (int)viewport.width, (int)viewport.height);
    }

    void GraphicsContextOGL::setConstant(const char* name, float value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform1f(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value);
    }

    void GraphicsContextOGL::setConstant(const char* name, int32_t value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform1i(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value);
    }

    void GraphicsContextOGL::setConstant(const char* name, uint32_t value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform1i(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value);
    }

    void GraphicsContextOGL::setConstant(const char* name, glm::vec2 value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform2f(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value.x, value.y);
    }

    void GraphicsContextOGL::setConstant(const char* name, glm::vec3 value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform3f(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value.x, value.y, value.z);
    }

    void GraphicsContextOGL::setConstant(const char* name, glm::vec4 value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform4f(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void GraphicsContextOGL::setConstant(const char* name, glm::mat4 value)
    {
        FFASSERT(boundProgram_);
        glProgramUniformMatrix4fv(boundProgram_->getId(), boundProgram_->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

} // namespace Ff