#include "Core/log.h"
#include <iostream>
#include <format>

#include "Platform/platform.h"
#include "Platform/window.h"

#include "graphicsContext.h"
#include "Shader/shaderProgram.h"
#include "glm/glm.hpp"
#include "Buffer/buffer.h"

using namespace Ff;

void init();
void update();

struct Vertex
{
    glm::vec3 position{};
    glm::vec3 color{};
};

int main()
{
    Log logger("Logger");
    Platform platform;
    Window window(800, 600, "Frameworkf");
    std::unique_ptr<GraphicsContext> context = GraphicsContext::create(&window);

    ShaderProgramSpec spec;
    spec.vertexShaderPath = "Framework/Shaders/testVS.glsl";
    spec.fragmentShaderPath = "Framework/Shaders/testFS.glsl";
    std::shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::create(spec);

    Vertex vertices[4]{
        { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
        { { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { { -0.5f, 0.5f, 0.0f }, { 0.5f, 0.0f, 0.5f } },

    };

    uint32_t indices[]
    {
        0, 1, 2, 
        2, 3, 0,
    };

    VertexBufferSpec vSpec;
    vSpec.size = sizeof(vertices);
    vSpec.stride = sizeof(Vertex);
    vSpec.layout.push_back(VertexLayoutElement{ 0, ShaderDataType::float3, offsetof(Vertex, position) });
    vSpec.layout.push_back(VertexLayoutElement{ 1, ShaderDataType::float3, offsetof(Vertex, color) });
    std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::create(vSpec);

    IndexBufferSpec iSpec;
    iSpec.size = sizeof(indices);
    std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::create(iSpec);

    vertexBuffer->write(vertices, sizeof(vertices));
    indexBuffer->write(indices, sizeof(indices));

    init();

    while (!window.shouldClose())
    {
        platform.pollEvents();
        Viewport2D viewport{};
        viewport.width = window.getWidth();
        viewport.height = window.getHeight();

        update();

        context->setViewport(viewport);
        context->useProgram(shaderProgram);
        context->setConstant("u_Offset", std::sin(glfwGetTime()) * 0.1f);
        
        context->bindVertexBuffer(vertexBuffer);
        context->bindIndexBuffer(indexBuffer);
        context->draw(6);

        window.swapBuffers();
    }
}