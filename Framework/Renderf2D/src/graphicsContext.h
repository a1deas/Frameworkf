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

    /** Viewport representation. */
    struct Viewport2D
    {
        /** x of the lower left corner of the viewport. */
        float x{};
        /** y of the lower left corner of the viewport. */
        float y{};
        /** Width of the viewport. */
        float width{ 1 };
        /** Height of the viewport. */
        float height{ 1 };
        /** Min depth of the viewport. */
        float minDepth{};
        /** Max depth of the viewport. */
        float maxDepth{ 1 };
    };

    extern RenderAPI gRenderAPI;

    class GraphicsContext
    {
    public:
        /**
         * Create graphics context, abstract data structure,
         * that stores all of the information and resources needed for rendering. 
         * @param window Window to which graphics context is bounded. 
         */
        GraphicsContext(Window* window);

        ~GraphicsContext();

        /** Factory that simplifies context creation.*/
        static std::unique_ptr<GraphicsContext> create(Window* window);

        /** Clears currently bound framebuffer to preset values at the beginning of a rendering cycle. */
        void clear();

        /**
         * Chooses shader program to use. 
         * @param program Shader program, that becomes active.
         */
        void useProgram(std::shared_ptr<ShaderProgram> program);

        /** Binds vertex buffer. */
        void bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
        /** Binds index buffer.  */
        void bindIndexBuffer(std::shared_ptr<IndexBuffer> buffer);
        /**
         * Binds texture to the slot.
         * @param texture texture, that we are binding.
         * @param slot slot to which texture will be bound.
         */
        void bindTexture(std::shared_ptr<Texture> texture, uint32_t slot = 0);

        /** Binds framebuffer. */
        void bindFramebuffer(std::shared_ptr<Framebuffer> framebuffer);
        /** Unbinds framebuffer. */
        void unbindFramebuffer();

        /** Draws primitives with the specified index count. */
        void drawElements(uint32_t indexCount);
        /** Draws primitives with the specified count of vertices. */
        void draw(uint32_t vertexCount);

        /** Specifies the viewport, to which context will be rendered. */
        void setViewport(Viewport2D viewport);

        /** Sets float constant. */
        void setConstant(const char* name, float value);
        /** Sets int32_t constant. */
        void setConstant(const char* name, int32_t value);
        /** Sets uint32_t constant. */
        void setConstant(const char* name, uint32_t value);
        /** Sets glm::vec2 constant. */
        void setConstant(const char* name, glm::vec2 value);
        /** Sets glm::vec3 constant. */
        void setConstant(const char* name, glm::vec3 value);
        /** Sets glm::vec4 constant. */
        void setConstant(const char* name, glm::vec4 value);
        /** Sets glm::mat4 constant. */
        void setConstant(const char* name, glm::mat4 value);

        /** Returns graphics context instance.*/
        static GraphicsContext& getInstance()
        {
            return *m_Instance;
        }
    private:
        static GraphicsContext* m_Instance;
        std::shared_ptr<ShaderProgram> m_BoundProgram;
        Window* m_Window;
    };
} // namespace Ff