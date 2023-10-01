#pragma once
#include "buffer.h"

namespace Ff
{
	class VertexBuffer : public Buffer
    {
    public:
        VertexBuffer();

        static void specifyLayout();

    private:
        float positions[6]{
            -0.5f, -0.5f,
             0.0f,  0.5f,
             0.5f, -0.5f,
        };
    };
}