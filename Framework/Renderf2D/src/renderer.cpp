#include "renderer.h"
#include "graphicsContext.h"
#include "Core/profile.h"

namespace Ff
{
    void Renderer::draw(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer) const
    {
        GraphicsContext::getInstance().bindVertexBuffer(vertexBuffer);
        GraphicsContext::getInstance().bindIndexBuffer(indexBuffer);

        GraphicsContext::getInstance().drawElements(indexBuffer->getIndexCount());
    }

    void Renderer::beginScene(std::shared_ptr<ShaderProgram> shader) const
    {
        FF_PROFILE_SCOPE();
        GraphicsContext::getInstance().useProgram(shader);
    }

    void Renderer::endScene() const
    {
    }

} // namespace Ff