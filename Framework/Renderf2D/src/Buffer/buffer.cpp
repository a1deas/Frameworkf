#include "Core/log.h"
#include "buffer.h"
#include "graphicsContext.h"
#include "Buffer/buffer.h"
#include "OpenGL/openGLUtils.h"
#include "glad/glad.h"

namespace Ff
{
    static constexpr uint32_t getComponentCount(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::float1:
                return 1;
            case ShaderDataType::float2:
                return 2;
            case ShaderDataType::float3:
                return 3;
            case ShaderDataType::float4:
                return 4;
        }
        FFABORT("UNKNOWN");
        return 0;
    }

    static constexpr uint32_t getComponentType(ShaderDataType type)
    {
        switch (type)
        {
            case Ff::ShaderDataType::float1:
            case Ff::ShaderDataType::float2:
            case Ff::ShaderDataType::float3:
            case Ff::ShaderDataType::float4:
                return GL_FLOAT;
        }
        FFABORT("UNKNOWN TYPE");
        return 0;
    }

    VertexBuffer::VertexBuffer(const VertexBufferSpec& spec)
        : spec(spec)
    {
        FFASSERT(spec.size > 0);
        glGenBuffers(1, &m_Buffer);
        glGenVertexArrays(1, &m_VertexArray);

        uint32_t prevBuffer = getCurrentGLBinding(GL_ARRAY_BUFFER_BINDING);
        uint32_t prevArray = getCurrentGLBinding(GL_VERTEX_ARRAY_BINDING);

        glBindVertexArray(m_VertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
        {
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(spec.size), nullptr,
                spec.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
            for (VertexLayoutElement element : spec.layout)
            {
                glEnableVertexAttribArray(element.attrib);
                glVertexAttribPointer(element.attrib, getComponentCount(element.type), getComponentType(element.type), false, spec.stride, (const void*)element.offset);
            }
        }
        //Must unbind vertex array first
        glBindVertexArray(prevArray);
        glBindBuffer(GL_ARRAY_BUFFER, prevBuffer);
    }

    VertexBuffer::~VertexBuffer()
    {
        if (m_Buffer)
        {
            glDeleteBuffers(1, &m_Buffer);
        }
        if (m_VertexArray)
        {
            glDeleteVertexArrays(1, &m_VertexArray);
        }
    }

    void VertexBuffer::write(const void* data, size_t size, size_t offset /*= 0*/)
    {
        uint32_t prevBuffer = getCurrentGLBinding(GL_ARRAY_BUFFER_BINDING);

        glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
        {
            glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
        }
        glBindBuffer(GL_ARRAY_BUFFER, prevBuffer);
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::create(const VertexBufferSpec& spec)
    {
        switch (gRenderAPI)
        {
            case RenderAPI::OpenGL:
                return std::make_shared<VertexBuffer>(spec);
            case RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }

    std::shared_ptr<Ff::IndexBuffer> IndexBuffer::create(const IndexBufferSpec& spec)
    {
        switch (gRenderAPI)
        {
            case RenderAPI::OpenGL:
                return std::make_shared<IndexBuffer>(spec);
            case RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }

    IndexBuffer::IndexBuffer(const IndexBufferSpec& spec)
        : spec(spec)
    {
        FFASSERT(spec.size > 0);

        glGenBuffers(1, &buffer);

        uint32_t prevBuffer = getCurrentGLBinding(GL_ELEMENT_ARRAY_BUFFER_BINDING);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(spec.size), nullptr,
            spec.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prevBuffer);
    }

    IndexBuffer::~IndexBuffer()
    {
        if (buffer)
        {
            glDeleteBuffers(1, &buffer);
        }
    }

    void IndexBuffer::write(const void* data, size_t size, size_t offset /*= 0*/)
    {
        uint32_t prevBuffer = getCurrentGLBinding(GL_ELEMENT_ARRAY_BUFFER_BINDING);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prevBuffer);
    }
} // namespace Ff