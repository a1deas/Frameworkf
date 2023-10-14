#include "Core/log.h"
#include "glad/glad.h"
#include "vertexBufferOGL.h"
#include "openGLUtils.h"

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

    VertexBufferOGL::VertexBufferOGL(const VertexBufferSpec& spec)
        : VertexBuffer(spec)
    {
        FFASSERT(spec.size > 0);

        glGenBuffers(1, &buffer_);
        glGenVertexArrays(1, &vertexArray_);

        uint32_t prevBuffer = getCurrentGLBinding(GL_ARRAY_BUFFER_BINDING);
        uint32_t prevArray = getCurrentGLBinding(GL_VERTEX_ARRAY_BINDING);

        glBindVertexArray(vertexArray_);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_);
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

    VertexBufferOGL::~VertexBufferOGL()
    {
        if (buffer_)
        {
            glDeleteBuffers(1, &buffer_);
        }
        if (vertexArray_)
        {
            glDeleteVertexArrays(1, &vertexArray_);
        }
    }

    void VertexBufferOGL::write(const void* data, size_t size, size_t offset /*= 0*/)
    {
        uint32_t prevBuffer = getCurrentGLBinding(GL_ARRAY_BUFFER_BINDING);

        glBindBuffer(GL_ARRAY_BUFFER, buffer_);
        {
            glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
        }
        glBindBuffer(GL_ARRAY_BUFFER, prevBuffer);
    }

} // namespace Ff