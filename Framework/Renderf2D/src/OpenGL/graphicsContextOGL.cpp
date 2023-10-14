#include "glad/glad.h"
#include "graphicsContextOGL.h"
#include "shaderProgramOGL.h"
#include "vertexBufferOGL.h"
#include "indexBufferOGL.h"
#include "glm/gtc/type_ptr.hpp"
#include "textureOGL.h"

namespace Ff
{
    static void openGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                FFTRACE("OpenGL: {}", message);
                break;
            case GL_DEBUG_SEVERITY_LOW:
                FFINFO("OpenGL: {}", message);
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                FFWARN("OpenGL: {}", message);
                break;
            case GL_DEBUG_SEVERITY_HIGH:
                FFERROR("OpenGL: {}", message);
                break;
        }
    }

    Ff::GraphicsContextOGL::GraphicsContextOGL(Window* window)
        : GraphicsContext(window)
    {
        glfwMakeContextCurrent(window->getWindow());

        if (!gladLoadGL())
        {
            FFABORT("OpenGL initialize failed!");
        }

        glDebugMessageCallback(openGLCallback, nullptr);
    }

    void GraphicsContextOGL::useProgram(std::shared_ptr<ShaderProgram> program)
    {
        auto glProgram = std::static_pointer_cast<ShaderProgramOGL>(program);
        glUseProgram(glProgram->getId());
        boundProgram_ = glProgram;
    }

    void GraphicsContextOGL::bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
    {
        auto vertexBuffer = std::static_pointer_cast<VertexBufferOGL>(buffer);
        glBindVertexArray(vertexBuffer->getVertexArray());
    }

    void GraphicsContextOGL::bindIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
    {
        auto indexBuffer = std::static_pointer_cast<IndexBufferOGL>(buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getBuffer());
    }

    void GraphicsContextOGL::bindTexture(std::shared_ptr<Texture> texture, uint32_t slot /*= 0*/)
    {
        auto textureOGL = std::static_pointer_cast<TextureOGL>(texture);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, textureOGL->getId());
    }

    void GraphicsContextOGL::drawElements(uint32_t indexCount)
    {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void GraphicsContextOGL::draw(uint32_t vertexCount)
    {
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));
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

    void GraphicsContextOGL::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

} // namespace Ff