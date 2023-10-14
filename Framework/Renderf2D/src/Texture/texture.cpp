#include "texture.h"
#include "graphicsContext.h"
#include "OpenGL/textureOGL.h"
#include "Core/log.h"

namespace Ff
{

    Texture::Texture(const TextureSpec& spec)
        : m_spec(spec)
    {
    }

    std::shared_ptr<Texture> Texture::create(const TextureSpec& spec)
    {
        switch (gRenderAPI)
        {

            case RenderAPI::OpenGL:
                return std::make_shared<TextureOGL>(spec);
            case RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }
} // namespace Ff