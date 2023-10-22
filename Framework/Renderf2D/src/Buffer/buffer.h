#pragma once
#include <cstdint>
#include <vector>
#include <memory>

namespace Ff
{
    class Buffer
    {
    public:
        virtual ~Buffer() = default;
        virtual void write(const void* data, size_t size, size_t offset = 0) = 0;
    };

    enum class ShaderDataType
    {
        float1,
        float2,
        float3,
        float4,
    };

    struct VertexLayoutElement
    {
        int32_t attrib{};
        ShaderDataType type{};
        size_t offset{};
    };

    struct VertexBufferSpec
    {
        std::vector<VertexLayoutElement> layout{};
        // Total buffer size
        size_t size{};
        // Size of a single vertex
        size_t stride{};
        // Will buffer change during its lifetime
        bool dynamic{};
    };

    struct IndexBufferSpec
    {
        // Total buffer size
        size_t size{};
        // Will buffer change during its lifetime
        bool dynamic{};
    };

    class VertexBuffer : public Buffer
    {
    public:
        VertexBuffer(const VertexBufferSpec& spec);
        ~VertexBuffer();
        
        static std::shared_ptr<VertexBuffer> create(const VertexBufferSpec& spec);
        virtual void write(const void* data, size_t size, size_t offset = 0) override;

        inline size_t getSize() const { return spec_.size; }
        inline uint32_t getVertexArray() const { return vertexArray_; }
    protected:
        VertexBufferSpec spec_;

    private:
        uint32_t buffer_{};
        uint32_t vertexArray_{};
    };

    //

    class IndexBuffer : public Buffer
    {
    public:
        IndexBuffer(const IndexBufferSpec& spec);
        ~IndexBuffer();

        static std::shared_ptr<IndexBuffer> create(const IndexBufferSpec& spec);
        virtual void write(const void* data, size_t size, size_t offset = 0) override;

        inline size_t getIndexCount() const { return spec_.size / sizeof(uint32_t); }
        uint32_t getBuffer() const { return buffer_; }

    protected:
        uint32_t buffer_{};
        IndexBufferSpec spec_;
    };
} // namespace Ff