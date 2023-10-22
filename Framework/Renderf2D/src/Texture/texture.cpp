#include "texture.h"
#include "graphicsContext.h"
#include "Texture/texture.h"
#include "Core/log.h"
#include "Vendor/stb_image.h"
#include "glad/glad.h"

namespace Ff
{
    int32_t toOGLInternalFormat(ImageFormat format)
    {
        switch (format)
        {
            case ImageFormat::RGBA:
                return GL_RGBA8;
            case ImageFormat::depthStencil:
                return GL_DEPTH24_STENCIL8;
            case ImageFormat::undefined:
                FFASSERT("UNDEFINED FORMAT");
        }
        return 0;
    }

    Texture::Texture(const TextureSpec& spec)
        : m_Spec(spec)
    {
        FFASSERT(!spec.path.empty());

        int width, height, bpp;

        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(spec.path.c_str(), &width, &height, &bpp, 4);

        FFASSERT(m_LocalBuffer);

        m_Width = width;
        m_Height = height;

        glGenTextures(1, &m_Id);
        glBindTexture(GL_TEXTURE_2D, m_Id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        if (m_LocalBuffer)
            stbi_image_free(m_LocalBuffer);
    }

    Texture::Texture(ImageFormat format, int width, int height)
        : m_Format(format)
        , m_Width(width)
        , m_Height(height)
    {
        glGenTextures(1, &m_Id);
        glBindTexture(GL_TEXTURE_2D, m_Id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexStorage2D(GL_TEXTURE_2D, 1, toOGLInternalFormat(format), width, height);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_Id);
    }

    std::shared_ptr<Texture> Texture::create(ImageFormat format, int width, int height)
    {
        switch (gRenderAPI)
        {

            case RenderAPI::OpenGL:
                return std::make_shared<Texture>(format, width, height);
            case RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }

    std::shared_ptr<Texture> Texture::create(const TextureSpec& spec)
    {
        switch (gRenderAPI)
        {

            case RenderAPI::OpenGL:
                return std::make_shared<Texture>(spec);
            case RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }
} // namespace Ff