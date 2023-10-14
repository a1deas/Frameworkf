#pragma once
#include "Texture/texture.h"

namespace Ff
{
    class TextureOGL : public Texture
    {
    public:
        TextureOGL(const TextureSpec& spec);
        ~TextureOGL();

        uint32_t getId() const { return m_Id; }

    private:
        uint32_t m_Id{};
    };
} // namespace Ff