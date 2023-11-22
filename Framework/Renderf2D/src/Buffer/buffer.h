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
        /** Binds buffer and updates a subset of a buffer object's data store. */
        virtual void write(const void* data, size_t size, size_t offset = 0) = 0;
    };

    enum class ShaderDataType
    {
        float1,
        float2,
        float3,
        float4,
    };

    struct VertexLayoutElement // !
    {
        int32_t attrib{};
        ShaderDataType type{};
        size_t offset{};
    };

    struct VertexBufferSpec
    {
        std::vector<VertexLayoutElement> layout{};
        // Total buffer size. 
        size_t size{};
        // Size of a single vertex. 
        size_t stride{};
        // Will buffer data change during its lifetime. 
        bool dynamic{};
    };

    struct IndexBufferSpec
    {
        // Total buffer size. 
        size_t size{};
        // Will buffer data change during its lifetime. 
        bool dynamic{};
    };

    class VertexBuffer : public Buffer
    {
    public:
        /** Creates vertex buffer with the specific data(from spec). */
        VertexBuffer(const VertexBufferSpec& spec);
        /** Deletes vertex buffer. */
        ~VertexBuffer();
        
        /** Factory that simplifies vertex buffer creation. */
        static std::shared_ptr<VertexBuffer> create(const VertexBufferSpec& spec);
        /** Binds buffer and updates a subset of a buffer object's data store. */
        virtual void write(const void* data, size_t size, size_t offset = 0) override;

        /** Returns spec size. */
        inline size_t getSize() const { return spec.size; }
        /** Returns vertex array. */
        inline uint32_t getVertexArray() const { return m_VertexArray; }
    protected:
        VertexBufferSpec spec;

    private:
        uint32_t m_Buffer{};
        uint32_t m_VertexArray{};
    };

    //

    class IndexBuffer : public Buffer
    {
    public:
        /** Creates index buffer with the specific data(from spec) */
        IndexBuffer(const IndexBufferSpec& spec);
        /** Deletes index buffer. */
        ~IndexBuffer();

        /** Factory that simplifies vertex buffer creation. */
        static std::shared_ptr<IndexBuffer> create(const IndexBufferSpec& spec);
        /** Binds buffer and updates a subset of a buffer object's data store. */
        virtual void write(const void* data, size_t size, size_t offset = 0) override;

        /** Returns index buffer's index count. */
        inline size_t getIndexCount() const { return spec.size / sizeof(uint32_t); }
        /** Returns index buffer. */
        uint32_t getBuffer() const { return buffer; }

    protected:
        uint32_t buffer{};
        IndexBufferSpec spec;
    };
} // namespace Ff