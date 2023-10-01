#include "buffer.h"
#include "graphicsContext.h"
#include "OpenGL/vertexBufferOGL.h"

namespace Ff
{

    std::shared_ptr<VertexBuffer> VertexBuffer::create(const VertexBufferSpec& spec)
    {
        switch (gRenderAPI)
        {
            case RenderAPI::OpenGL:
                return std::make_shared<VertexBufferOGL>(spec);
            case RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }
} // namespace Ff