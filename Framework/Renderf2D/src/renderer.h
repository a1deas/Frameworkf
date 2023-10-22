#pragma once
#include "Buffer/buffer.h"
#include "Shader/shaderProgram.h"

namespace Ff
{
    class Renderer
    {
    public:
        Renderer() = default;
        void draw(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer) const;
        void beginScene(std::shared_ptr<ShaderProgram> shader) const;
        void endScene() const;
    };
} // namespace Ff