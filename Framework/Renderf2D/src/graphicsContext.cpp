#include "Core/log.h"
#include "graphicsContext.h"
#include "glad/glad.h"
#include "Shader/shaderProgram.h"
#include "Buffer/buffer.h"
#include "glm/gtc/type_ptr.hpp"
#include "Texture/texture.h"
#include "Framebuffer/framebuffer.h"

namespace Ff
{
    RenderAPI gRenderAPI = RenderAPI::OpenGL;

    std::unique_ptr<GraphicsContext> GraphicsContext::create(Window* window)
    {
        switch (gRenderAPI)
        {
            case Ff::RenderAPI::OpenGL:
                return std::make_unique<GraphicsContext>(window);
            case Ff::RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }

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

    GraphicsContext::GraphicsContext(Window* window)
        : m_window(window)
    {
        instance = this;
        glfwMakeContextCurrent(window->getWindow());

        if (!gladLoadGL())
        {
            FFABORT("OpenGL initialize failed!");
        }

        glDebugMessageCallback(openGLCallback, nullptr);
    }

    GraphicsContext::~GraphicsContext()
    {
    }

    void GraphicsContext::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GraphicsContext::useProgram(std::shared_ptr<ShaderProgram> program)
    {
        auto glProgram = std::static_pointer_cast<ShaderProgram>(program);
        glUseProgram(glProgram->getId());
        boundProgram_ = glProgram;
    }

    void GraphicsContext::bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
    {
        auto vertexBuffer = std::static_pointer_cast<VertexBuffer>(buffer);
        glBindVertexArray(vertexBuffer->getVertexArray());
    }

    void GraphicsContext::bindIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
    {
        auto indexBuffer = std::static_pointer_cast<IndexBuffer>(buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getBuffer());
    }

    void GraphicsContext::bindTexture(std::shared_ptr<Texture> texture, uint32_t slot /*= 0*/)
    {
        auto textureOGL = std::static_pointer_cast<Texture>(texture);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, textureOGL->getId());
    }

    void GraphicsContext::bindFramebuffer(std::shared_ptr<Framebuffer> framebuffer)
    {
        auto framebufferOGL = std::static_pointer_cast<Framebuffer>(framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferOGL->getFramebuffer());
    }

    void GraphicsContext::unbindFramebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void GraphicsContext::drawElements(uint32_t indexCount)
    {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void GraphicsContext::draw(uint32_t vertexCount)
    {
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));
    }

    void GraphicsContext::setViewport(Viewport2D viewport)
    {
        glViewport((int)viewport.x, (int)viewport.y, (int)viewport.width, (int)viewport.height);
    }

    void GraphicsContext::setConstant(const char* name, float value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform1f(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value);
    }

    void GraphicsContext::setConstant(const char* name, int32_t value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform1i(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value);
    }

    void GraphicsContext::setConstant(const char* name, uint32_t value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform1i(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value);
    }

    void GraphicsContext::setConstant(const char* name, glm::vec2 value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform2f(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value.x, value.y);
    }

    void GraphicsContext::setConstant(const char* name, glm::vec3 value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform3f(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value.x, value.y, value.z);
    }

    void GraphicsContext::setConstant(const char* name, glm::vec4 value)
    {
        FFASSERT(boundProgram_);
        glProgramUniform4f(boundProgram_->getId(), boundProgram_->getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void GraphicsContext::setConstant(const char* name, glm::mat4 value)
    {
        FFASSERT(boundProgram_);
        glProgramUniformMatrix4fv(boundProgram_->getId(), boundProgram_->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    Ff::GraphicsContext* GraphicsContext::instance;

} // namespace Ff
