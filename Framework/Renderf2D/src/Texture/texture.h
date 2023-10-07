#pragma once

#include "renderer.h"

namespace Ff
{
    struct TextureSpec
    {
        std::string path;
    };

    class Texture
    {
    public:
        Texture(const TextureSpec& spec);
        virtual ~Texture() = default;

        static std::shared_ptr<Texture> create(const TextureSpec& spec);

        inline uint32_t getWidth() const { return m_Width; }
        inline uint32_t getHeigth() const { return m_Height; }

    protected:
        TextureSpec m_spec;
        uint8_t* m_LocalBuffer{};
        uint32_t m_Width{};
        uint32_t m_Height{};
        uint32_t m_BPP{};
    };
} // namespace Ff