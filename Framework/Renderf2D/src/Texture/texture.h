#pragma once

#include "renderer.h"

namespace Ff
{
    struct TextureSpec
    {
        /** Path to the texture. */
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
        /**
         * Creates texture.
         * @param format texture's format.
         * @param width texture's width.
         * @param height texture's height.
         */
        Texture(ImageFormat format, int width, int height);
        /** Creates texture with the path from spec. */
        Texture(const TextureSpec& spec);
        /** Deletes texture. */
        ~Texture();

        /**
         * Factory that simplifies texture creation.
         * @param format texture's format.
         * @param width texture's width.
         * @param height texture's height.
         */
        static std::shared_ptr<Texture> create(ImageFormat format, int width, int height);
        /** Factory that simplifies texture creation. Data is getting from the spec. */
        static std::shared_ptr<Texture> create(const TextureSpec& spec);

        /** Returns texture's width. */
        inline uint32_t getWidth() const { return width; }
        /** Returns texture's height. */
        inline uint32_t getHeigth() const { return height; }
        /** Returns texture's index. */
        uint32_t getId() const { return m_Id; }

    protected:
        TextureSpec spec;
        uint8_t* localBuffer{};
        uint32_t width{};
        uint32_t height{};
        ImageFormat format{ ImageFormat::RGBA };

    private:
        uint32_t m_Id{};
    };
} // namespace Ff