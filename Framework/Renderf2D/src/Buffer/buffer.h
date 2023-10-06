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
        VertexBuffer(const VertexBufferSpec& spec)
            : spec_(spec)
        {
        }

        inline size_t getSize() const { return spec_.size; }
        static std::shared_ptr<VertexBuffer> create(const VertexBufferSpec& spec);

    protected:
        VertexBufferSpec spec_;
    };

    class IndexBuffer : public Buffer
    {
    public:
        IndexBuffer(const IndexBufferSpec& spec)
            : spec_(spec)
        {
        }

        inline size_t getIndexCount() const { return spec_.size / sizeof(uint32_t); }
        static std::shared_ptr<IndexBuffer> create(const IndexBufferSpec& spec);


    protected:
        IndexBufferSpec spec_;
    };
} // namespace Ff