#include "uiContext.h"

namespace Ff
{
    void UIContext::init(const Window& window)
    {
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark(); 
    }

    void UIContext::begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void UIContext::end()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UIContext::destroyContext()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
} // namespace Ff