#pragma once
#include "Buffer/buffer.h"
#include "Shader/shaderProgram.h"

namespace Ff
{
    class Renderer
    {
    public:
        Renderer() = default;
        /** Draws primitives, using data from vertex and index buffers. */
        void draw(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer) const;
        /** Begins rendering scene. */
        void beginScene(std::shared_ptr<ShaderProgram> shader) const;
        /** Finishes scene render. */
        void endScene() const;
    };
} // namespace Ff