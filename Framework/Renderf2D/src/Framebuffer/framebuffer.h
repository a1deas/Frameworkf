#pragma once
#include "Texture/texture.h"
#include <memory>

namespace Ff
{
    struct FramebufferSpec
    {
        int width{};
        int height{};
        std::vector<ImageFormat> colorAttachments;
        ImageFormat depthAttachment{};
    };

    class Framebuffer
    {
    public:
        Framebuffer(const FramebufferSpec& spec);
        ~Framebuffer();

        virtual uint32_t getColorAttachment(uint32_t index = 0);
        uint32_t getFramebuffer() { return m_Framebuffer_; }

        static std::shared_ptr<Framebuffer> create(const FramebufferSpec& spec);

    protected:
        FramebufferSpec spec_;
        uint32_t m_Framebuffer_{};
        std::vector<std::shared_ptr<Texture>> textures;
    };
} // namespace Ff