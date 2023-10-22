#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Platform/window.h"
#include "Shader/shaderProgram.h"
#include "Buffer/buffer.h"
#include "Texture/texture.h"
#include "Framebuffer/framebuffer.h"

namespace Ff
{
    enum class RenderAPI
    {
        OpenGL,
        None,
    };

    struct Viewport2D
    {
        float x{};
        float y{};
        float width{ 1 };
        float height{ 1 };
        float mindepth{};
        float maxdepth{ 1 };
    };

    extern RenderAPI gRenderAPI;

    class GraphicsContext
    {
    public:
        GraphicsContext(Window* window);

        ~GraphicsContext();

        static std::unique_ptr<GraphicsContext> create(Window* window);

        virtual void clear();

        virtual void useProgram(std::shared_ptr<ShaderProgram> program);

        virtual void bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
        virtual void bindIndexBuffer(std::shared_ptr<IndexBuffer> buffer);
        virtual void bindTexture(std::shared_ptr<Texture> texture, uint32_t slot = 0);

        virtual void bindFramebuffer(std::shared_ptr<Framebuffer> framebuffer);
        virtual void unbindFramebuffer();

        virtual void drawElements(uint32_t indexCount);

        virtual void draw(uint32_t vertexCount);

        virtual void setViewport(Viewport2D viewport);

        virtual void setConstant(const char* name, float value);
        virtual void setConstant(const char* name, int32_t value);
        virtual void setConstant(const char* name, uint32_t value);
        virtual void setConstant(const char* name, glm::vec2 value);
        virtual void setConstant(const char* name, glm::vec3 value);
        virtual void setConstant(const char* name, glm::vec4 value);
        virtual void setConstant(const char* name, glm::mat4 value);

        static GraphicsContext& getInstance()
        {
            return *instance;
        }
    private:
        static GraphicsContext* instance;
        std::shared_ptr<ShaderProgram> boundProgram_;
        Window* m_window;
    };
} // namespace Ff