#include "Core/log.h"
#include "textureOGL.h"
#include "glad/glad.h"
#include "Vendor/stb_image.h"

namespace Ff
{

    TextureOGL::TextureOGL(const TextureSpec& spec)
        : Texture(spec)
    {
        FFASSERT(!spec.path.empty());

        int width, height, bpp;

        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(spec.path.c_str(), &width, &height, &bpp, 4);

        FFASSERT(m_LocalBuffer);

        m_Width = width;
        m_Height = height;
        m_BPP = bpp;

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

    TextureOGL::~TextureOGL()
    {
        glDeleteTextures(1, &m_Id);
    }

} // namespace Ff