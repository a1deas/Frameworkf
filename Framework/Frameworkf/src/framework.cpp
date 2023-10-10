#include "Core/log.h"
#include <iostream>
#include <format>

#include "Platform/platform.h"
#include "Platform/window.h"

#include "graphicsContext.h"
#include "Shader/shaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Buffer/buffer.h"
#include "UI/uiContext.h"
#include "renderer.h"
#include "Texture/texture.h"

using namespace Ff;

void init();
void update();

struct Vertex
{
    glm::vec3 position{};
    glm::vec3 color{};
    glm::vec2 uv{};
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
    Window window(800, 600, "Frameworkf");
    std::unique_ptr<GraphicsContext> context = GraphicsContext::create(&window);
    UIContext::init(window);
    Renderer renderer;

    ShaderProgramSpec spec;
    spec.vertexShaderPath = "Framework/Shaders/testVS.glsl";
    spec.fragmentShaderPath = "Framework/Shaders/testFS.glsl";
    std::shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::create(spec);

    Vertex vertices[4]{
        { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.5f, 0.5f, 0.0f }, { 0.5f, 0.0f, 0.5f }, { 0.0f, 1.0f } },

    };

    Triangle indices[] = {
        { 0, 1, 2 },
        { 2, 3, 0 },
    };

    VertexBufferSpec vSpec;
    vSpec.size = sizeof(vertices);
    vSpec.stride = sizeof(Vertex);
    vSpec.layout.push_back(VertexLayoutElement{ 0, ShaderDataType::float3, offsetof(Vertex, position) });
    vSpec.layout.push_back(VertexLayoutElement{ 1, ShaderDataType::float3, offsetof(Vertex, color) });
    vSpec.layout.push_back(VertexLayoutElement{ 2, ShaderDataType::float2, offsetof(Vertex, uv) });
    std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::create(vSpec);

    IndexBufferSpec iSpec;
    iSpec.size = sizeof(indices);
    std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::create(iSpec);

    vertexBuffer->write(vertices, sizeof(vertices));
    indexBuffer->write(indices, sizeof(indices));

    TextureSpec tSpec;
    tSpec.path = "resources/textures/photo.png";
    std::shared_ptr<Texture> texture = Texture::create(tSpec);

    init();

    glfwSwapInterval(0);
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);

    float x = 1.0f;
    float _x = 0.05f;
    //
    bool show_demo_window = true;
    bool show_another_window = true;
    glm::vec4 clear_color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    //

    while (!window.shouldClose())
    {
        platform.pollEvents();
        Viewport2D viewport{};
        viewport.width = window.getWidth();
        viewport.height = window.getHeight();

        float aspectRatio = viewport.width / viewport.height;
        float displayWidth = 4.0f;
        float displayHeight = displayWidth / aspectRatio;

        const float halfDisplayWidth = displayWidth * 0.5f;
        const float halfDisplayHeight = displayHeight * 0.5f;

        glm::mat4 proj = glm::ortho(-halfDisplayWidth, halfDisplayWidth, -halfDisplayHeight, halfDisplayHeight, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), -glm::vec3(x, 0.0f, 0.0f));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        update();

        context->clear();

        UIContext::begin();
        renderer.beginScene(shaderProgram);

        context->bindTexture(texture);
        context->setConstant("u_Texture", int32_t(0));
        context->setViewport(viewport);
        context->setConstant("u_Color", glm::vec4(color, 1.0f));

        context->setConstant("u_MVP", proj * view * model);

        renderer.draw(vertexBuffer, indexBuffer);

        //
        {
            ImGui::Begin("Frameworkf");
            ImGui::SliderFloat3("Color##1", &color.r, 0.0f, 1.0f);
            ImGui::ColorEdit3("Color##2", (float*)&color.r);
            if (ImGui::Button("<--"))
                x += _x;
            ImGui::SameLine();
            if (ImGui::Button("-->"))
                x -= _x;

            ImGuiIO& io = ImGui::GetIO();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        //

        renderer.endScene();
        UIContext::end();

        window.swapBuffers();
    }
    UIContext::destroyContext();
}