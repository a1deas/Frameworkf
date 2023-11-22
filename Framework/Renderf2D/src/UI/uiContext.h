#pragma once
#include "Platform/window.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

namespace Ff
{
    class UIContext
    {
    public:
        /** Creates and setups ImGui context to the specified window. */
        static void init(const Window& window);
        /** Starts new frame */
        static void begin();
        /** Renders ImGui to viewport. */
        static void end();
        /** Shutdowns ImGui and destroys its context. */
        static void destroyContext();
    };
} // namespace Ff