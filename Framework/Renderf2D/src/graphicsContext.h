#pragma once

#include <memory>

#include "Platform/window.h"
#include "Shader/shaderProgram.h"

namespace Ff
{
    enum class RenderAPI
    {
        OpenGL,
        None,
    };

    extern RenderAPI gRenderAPI;

    class GraphicsContext
    {
    public:
        GraphicsContext(Window* window)
            : m_window(window)
        {
        }

        virtual ~GraphicsContext() = default;
        static std::unique_ptr<GraphicsContext> create(Window* window);

        virtual void useProgram(std::shared_ptr<ShaderProgram> program) = 0;

    protected:
        Window* m_window;
    };
} // namespace Ff