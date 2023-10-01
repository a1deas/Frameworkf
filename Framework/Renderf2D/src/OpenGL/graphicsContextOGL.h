#pragma once
#include "graphicsContext.h"

namespace Ff
{
    class GraphicsContextOGL : public GraphicsContext
    {
    public:
        GraphicsContextOGL(Window* window);

        virtual void useProgram(std::shared_ptr<ShaderProgram> program) override;
    };
} // namespace Ff