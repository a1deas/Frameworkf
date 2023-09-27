#pragma once

#include "graphicsContext.h"

namespace Ff
{
    class GraphicsContextOGL : public GraphicsContext
    {
    public:
        GraphicsContextOGL(Window* window);
    };
} // namespace Ff