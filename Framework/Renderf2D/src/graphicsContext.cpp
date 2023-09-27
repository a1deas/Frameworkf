#include "graphicsContext.h"
#include "OpenGL/graphicsContextOGL.h"

namespace Ff
{
    RenderAPI gRenderAPI = RenderAPI::OpenGL;

    std::unique_ptr<GraphicsContext> GraphicsContext::create(Window* window)
    {
        switch (gRenderAPI)
        {
            case Ff::RenderAPI::OpenGL:
                return std::make_unique<GraphicsContextOGL>(window);
            case Ff::RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }

} // namespace Ff
