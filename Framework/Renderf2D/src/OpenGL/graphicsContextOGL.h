#pragma once
#include "graphicsContext.h"
#include "shaderProgramOGL.h"

namespace Ff
{
    class GraphicsContextOGL : public GraphicsContext
    {
    public:
        GraphicsContextOGL(Window* window);

        virtual void useProgram(std::shared_ptr<ShaderProgram> program) override;

        virtual void bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer) override;
        virtual void bindIndexBuffer(std::shared_ptr<IndexBuffer> buffer) override;
        virtual void bindTexture(std::shared_ptr<Texture> texture, uint32_t slot = 0) override;

        virtual void drawElements(uint32_t indexCount) override;

        virtual void draw(uint32_t vertexCount) override;

        virtual void setViewport(Viewport2D viewport) override;

        virtual void setConstant(const char* name, float value) override;
        virtual void setConstant(const char* name, int32_t value) override;
        virtual void setConstant(const char* name, uint32_t value) override;
        virtual void setConstant(const char* name, glm::vec2 value) override;
        virtual void setConstant(const char* name, glm::vec3 value) override;
        virtual void setConstant(const char* name, glm::vec4 value) override;
        virtual void setConstant(const char* name, glm::mat4 value) override;

        virtual void clear() override;


    private:
        std::shared_ptr<ShaderProgramOGL> boundProgram_;
    };
} // namespace Ff