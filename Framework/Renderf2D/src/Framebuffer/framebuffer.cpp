#include "framebuffer.h"
#include "graphicsContext.h"
#include "Framebuffer/framebuffer.h"
#include "glad/glad.h"
#include "OpenGL/openGLUtils.h"

namespace Ff
{

    Framebuffer::Framebuffer(const FramebufferSpec& spec)
        : spec_(spec)
    {
        glGenFramebuffers(1, &m_Framebuffer_);

        uint32_t prevBuffer = getCurrentGLBinding(GL_FRAMEBUFFER_BINDING);

        glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer_);

        std::vector<uint32_t> writeAttachments;
        uint32_t index = 0;

        for (ImageFormat attachment : spec.colorAttachments)
        {
            std::shared_ptr<Texture> texture = Texture::create(attachment, spec.width, spec.height);
            std::shared_ptr<Texture> textureOGL = std::static_pointer_cast<Texture>(texture);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, textureOGL->getId(), 0);
            writeAttachments.push_back(GL_COLOR_ATTACHMENT0 + index);
            textures.push_back(textureOGL);
            index++;
        }

        glDrawBuffers(writeAttachments.size(), writeAttachments.data());

        if (spec.depthAttachment != ImageFormat::undefined)
        {
            std::shared_ptr<Texture> texture = Texture::create(spec.depthAttachment, spec.width, spec.height);
            std::shared_ptr<Texture> textureOGL = std::static_pointer_cast<Texture>(texture);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textureOGL->getId(), 0);
            textures.push_back(textureOGL);
        }

        FFASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        glBindFramebuffer(GL_FRAMEBUFFER, prevBuffer);
    }

    Framebuffer::~Framebuffer()
    {
        if (m_Framebuffer_)
        {
            glDeleteFramebuffers(1, &m_Framebuffer_);
        }
    }

    uint32_t Framebuffer::getColorAttachment(uint32_t index /*= 0*/)
    {
        return textures[index]->getId();
    }

    std::shared_ptr<Ff::Framebuffer> Framebuffer::create(const FramebufferSpec& spec)
    {
        switch (gRenderAPI)
        {
            case RenderAPI::OpenGL:
                return std::make_shared<Framebuffer>(spec);
            case RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }

} // namespace Ff