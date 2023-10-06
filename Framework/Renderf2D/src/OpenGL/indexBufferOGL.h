#pragma once
#include "Buffer/buffer.h"

namespace Ff
{
    class IndexBufferOGL : public IndexBuffer
    {
    public:
        IndexBufferOGL(const IndexBufferSpec& spec);
        ~IndexBufferOGL();

        virtual void write(const void* data, size_t size, size_t offset = 0) override;

        uint32_t getBuffer() const { return buffer_; }
    private:
        uint32_t buffer_{};
    };
} // namespace Ff