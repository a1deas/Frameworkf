#include "Core/log.h"
#include "glad/glad.h"
#include "indexBufferOGL.h"
#include "openGLUtils.h"

namespace Ff
{

    IndexBufferOGL::IndexBufferOGL(const IndexBufferSpec& spec)
        : IndexBuffer(spec)
    {
        FFASSERT(spec.size > 0);

        glGenBuffers(1, &buffer_);

        uint32_t prevBuffer = getCurrentGLBinding(GL_ELEMENT_ARRAY_BUFFER_BINDING);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(spec.size), nullptr,
            spec.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prevBuffer);
    }

    IndexBufferOGL::~IndexBufferOGL()
    {
        if (buffer_)
        {
            glDeleteBuffers(1, &buffer_);
        }
    }

    void IndexBufferOGL::write(const void* data, size_t size, size_t offset /*= 0*/)
    {
        uint32_t prevBuffer = getCurrentGLBinding(GL_ELEMENT_ARRAY_BUFFER_BINDING);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_);
        {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prevBuffer);
    }

} // namespace Ff