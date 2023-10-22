#pragma once

#include "renderer.h"

namespace Ff
{
    struct TextureSpec
    {
        std::string path;
    };

    enum class ImageFormat
    {
        undefined,
        RGBA,
        R32uint,
        depthStencil,
    };

    class Texture
    {
    public:
        Texture(ImageFormat format, int width, int height);
        Texture(const TextureSpec& spec);
        ~Texture();

        static std::shared_ptr<Texture> create(const TextureSpec& spec);
        static std::shared_ptr<Texture> create(ImageFormat format, int width, int height);

        inline uint32_t getWidth() const { return m_Width; }
        inline uint32_t getHeigth() const { return m_Height; }

        uint32_t getId() const { return m_Id; }

    protected:
        TextureSpec m_Spec;
        uint8_t* m_LocalBuffer{};
        uint32_t m_Width{};
        uint32_t m_Height{};
        ImageFormat m_Format{ ImageFormat::RGBA };

    private:
        uint32_t m_Id{};
    };
} // namespace Ff