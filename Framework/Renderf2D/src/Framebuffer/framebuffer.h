#pragma once
#include "Texture/texture.h"
#include <memory>

namespace Ff
{
    /** Specifies framebuffer. */
    struct FramebufferSpec
    {
        /** Framebuffer width. */
        int width{};
        /** Framebuffer height. */
        int height{};
        /** Texture formats. */
        std::vector<ImageFormat> colorAttachments;
        /** Depth attachment format. */
        ImageFormat depthAttachment{};
    };

    class Framebuffer
    {
    public:
        /** Creates framebuffer with the data from framebuffer spec. */
        Framebuffer(const FramebufferSpec& spec);
        /** Deletes framebuffer. */
        ~Framebuffer();

        /** Returns color attachments. */
        virtual uint32_t getColorAttachment(uint32_t index = 0);
        /** Returns framebuffer. */
        uint32_t getFramebuffer() { return framebuffer; }

        /** Factory that simplifies framebuffer creation. */
        static std::shared_ptr<Framebuffer> create(const FramebufferSpec& spec);

    protected:
        FramebufferSpec spec;
        uint32_t framebuffer{};
        std::vector<std::shared_ptr<Texture>> textures;
    };
} // namespace Ff