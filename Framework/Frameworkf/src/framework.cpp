#include "Core/log.h"
#include "Core/profile.h"
#include "Core/timers.h"

#include <iostream>
#include <format>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Platform/platform.h"
#include "Platform/window.h"
#include "Platform/input.h"

#include "renderer.h"
#include "graphicsContext.h"
#include "Shader/shaderProgram.h"
#include "Buffer/buffer.h"
#include "UI/uiContext.h"
#include "Texture/texture.h"
#include "Camera/camera.h"
#include "Framebuffer/framebuffer.h"

using namespace Ff;

void init();
void update();

struct Vertex
{
    glm::vec3 position{};
    glm::vec3 color{};
    glm::vec2 uv{};
    float texId{};
};

struct Triangle
{
    uint32_t p0{};
    uint32_t p1{};
    uint32_t p2{};
};

int main()
{
    Log logger("Logger");
    Platform platform;
    Window window(1280, 720, "Frameworkf");
    std::unique_ptr<GraphicsContext> context = GraphicsContext::create(&window);
    UIContext::init(window);
    Renderer renderer;
    Camera camera;
    Timer mainTimer;

    camera.width = 8.0f;

    ShaderProgramSpec spec;
    spec.vertexShaderPath = "Framework/Shaders/testVS.glsl";
    spec.fragmentShaderPath = "Framework/Shaders/testFS.glsl";
    std::shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::create(spec);

    Vertex vertices[]{
        { { -1.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, 0.0f },
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }, 0.0f },
        { { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, 0.0f },
        { { -1.5f,  0.5f, 0.0f }, { 0.5f, 0.0f, 0.5f }, { 0.0f, 1.0f }, 0.0f },

        { { 0.5f, -0.5f, 0.0f }, { 0.5f, 0.0f, 0.5f }, { 0.0f, 0.0f }, 1.0f },
        { { 1.5f, -0.5f, 0.0f }, { 0.5f, 0.0f, 0.5f }, { 1.0f, 0.0f }, 1.0f },
        { { 1.5f, 0.5f, 0.0f }, { 0.5f, 0.0f, 0.5f }, { 1.0f, 1.0f }, 1.0f },
        { { 0.5f, 0.5f, 0.0f }, { 0.5f, 0.0f, 0.5f }, { 0.0f, 1.0f }, 1.0f },
    };

    Triangle indices[] = {
        { 0, 1, 2 },
        { 2, 3, 0 },

        { 4, 5, 6},
        { 6, 7, 4}
    };

    VertexBufferSpec vSpec;
    vSpec.size = sizeof(vertices);
    vSpec.stride = sizeof(Vertex);
    vSpec.layout.push_back(VertexLayoutElement{ 0, ShaderDataType::float3, offsetof(Vertex, position) });
    vSpec.layout.push_back(VertexLayoutElement{ 1, ShaderDataType::float3, offsetof(Vertex, color) });
    vSpec.layout.push_back(VertexLayoutElement{ 2, ShaderDataType::float2, offsetof(Vertex, uv) });
    vSpec.layout.push_back(VertexLayoutElement{ 3, ShaderDataType::float1, offsetof(Vertex, texId) });
    std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::create(vSpec);

    IndexBufferSpec iSpec;
    iSpec.size = sizeof(indices);
    std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::create(iSpec);

    vertexBuffer->write(vertices, sizeof(vertices));
    indexBuffer->write(indices, sizeof(indices));

    FramebufferSpec fSpec;
    fSpec.colorAttachments.push_back(ImageFormat::RGBA);
    fSpec.width = window.getWidth();
    fSpec.height = window.getHeight();


    std::shared_ptr<Framebuffer> framebuffer = Framebuffer::create(fSpec);

    TextureSpec tSpecA;
    tSpecA.path = "resources/textures/roland.png";

    TextureSpec tSpecB;
    tSpecB.path = "resources/textures/roland.png";

    std::shared_ptr<Texture> textureA = Texture::create(tSpecA);
    std::shared_ptr<Texture> textureB = Texture::create(tSpecB);

    init();

    glfwSwapInterval(0);
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    glm::vec3 color = glm::vec3(0.9f, 0.5f, 0.1f);
    float incrementr = 0.05f;
    float incrementb = 0.05f;

    glm::vec4 clear_color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

    float x1 = 1.0f;
    float x2 = 1.0f;
    float _x = 0.05f;

    //
    bool show_demo_window = true;
    bool show_another_window = true;
    //


    while (!window.shouldClose())
    {
        FF_PROFILE_FRAME("Game Loop");
        mainTimer.start();
        platform.pollEvents();
        Viewport2D viewport{};
        viewport.width = window.getWidth();
        viewport.height = window.getHeight();

        update();

        context->bindFramebuffer(framebuffer);
        context->clear();
        renderer.beginScene(shaderProgram);

        glm::mat4 proj1 = camera.generateProjMatrix(viewport);
        glm::mat4 view1 = camera.generateViewMatrix(0.0f, 0.0f);
        
        camera.controlCamera(mainTimer.getDelta());
        
        context->bindTexture(textureA, 0);
        context->bindTexture(textureB, 1);
        
        context->setConstant("u_MVP", proj1 * view1);
        context->setConstant("u_Color", glm::vec4(color, 1.0f));
        context->setConstant("u_Texture[0]", int32_t(0));
        context->setConstant("u_Texture[1]", int32_t(1));
        context->setViewport(viewport);

        renderer.draw(vertexBuffer, indexBuffer);
        renderer.endScene();

        context->unbindFramebuffer();
        context->clear();

        UIContext::begin();
        
        ImGui::DockSpaceOverViewport();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
        if (ImGui::Begin("Viewport"))
        {
            FF_PROFILE_SCOPE("Begin Viewport");
            ImGui::Image(reinterpret_cast<ImTextureID>(framebuffer->getColorAttachment()), 
                ImGui::GetContentRegionAvail(),
                ImVec2(0, 1), ImVec2(1, 0));
        } 

        ImGui::End();
        ImGui::PopStyleVar();
        
        //
        {
            FF_PROFILE_SCOPE("Properties scope");
            ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoCollapse);
            ImGui::SliderFloat3("Color1##1", &color.r, 0.0f, 1.0f);
            ImGui::ColorEdit3("Color1##2", (float*)&color.r);

            ImGui::SliderFloat3("Color2##1", &color.r, 0.0f, 1.0f);
            ImGui::ColorEdit3("Color2##2", (float*)&color.r);

            ImGui::DragFloat("dragSpeed", &camera.speedConst, 0.001f);

            static bool check = false;
            ImGui::Checkbox("RGB - rand", &check);
            if (check)
            {
                if (color.r > 1.0f)
                    incrementr = -0.05f;
                if (color.r < 0.0f)
                    incrementr = 0.05f;

                if (color.b > 1.0f)
                    incrementb = -0.05f;
                if (color.b < 0.0f)
                    incrementb = 0.05f;

                color.r += incrementr;
                color.b += incrementb;
            }

            ImGuiIO& io = ImGui::GetIO();
            ImGui::Text("Application average %.3f ms", 1000.0f / io.Framerate);
            ImGui::Text("Application frame (%.1f FPS)", io.Framerate);
            ImGui::Text("Camera position: x:%.1f, y:%.1f, z:%.1f", camera.position.x, camera.position.y, camera.position.z);
            ImGui::Text("Scroll Offset: y:%.1f", Input::getScrollOffset());
            ImGui::End();
        }

        UIContext::end();

        window.swapBuffers();
        Input::resetOffsets();
        mainTimer.end();
    }
    UIContext::destroyContext();
}