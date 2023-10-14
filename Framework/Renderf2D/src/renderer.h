#pragma once

#include "OpenGL/vertexBufferOGL.h"
#include "OpenGL/indexBufferOGL.h"
#include "OpenGL/shaderProgramOGL.h"

namespace Ff
{
    class Renderer
    {
    public:
        Renderer() = default;
        void draw(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer) const;
        void beginScene(std::shared_ptr<ShaderProgram> shader) const;
        void endScene() const;

    private:
    };
} // namespace Ff