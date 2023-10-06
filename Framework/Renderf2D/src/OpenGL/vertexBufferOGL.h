#pragma once
#include "Buffer/buffer.h"

namespace Ff
{
    class VertexBufferOGL : public VertexBuffer
    {
    public:
        VertexBufferOGL(const VertexBufferSpec& spec);
        ~VertexBufferOGL();

        virtual void write(const void* data, size_t size, size_t offset = 0) override;

        inline uint32_t getVertexArray() const { return vertexArray_; }
    private:
        uint32_t buffer_{};
        uint32_t vertexArray_{};
    };
} // namespace Ff