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
        static void init(const Window& window);
        static void begin();
        static void end();
        static void destroyContext();
    };
} // namespace Ff