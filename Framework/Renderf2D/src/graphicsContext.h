#pragma once

#include <memory>

#include "Platform/window.h"

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

    protected:
        Window* m_window;
    };
} // namespace Ff