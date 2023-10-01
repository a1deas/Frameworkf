#include "vertexBuffer.h"
#include "glad/glad.h"

namespace Ff
{

    VertexBuffer::VertexBuffer()
        : Buffer()
    {
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    }

    void VertexBuffer::specifyLayout()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    }

} // namespace Ff