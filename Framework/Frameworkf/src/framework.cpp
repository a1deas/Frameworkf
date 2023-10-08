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

    glfwSwapInterval(2);
    float x = 0.5f;
    float y = 0.7f;
    float z{};

    float increment = 0.05f;

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
        glm::mat4 view = glm::translate(glm::mat4(1.0f), -glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        update();

        context->clear();

        renderer.beginScene(shaderProgram);

        context->bindTexture(texture);
        context->setConstant("u_Texture", int32_t(0));
        context->setViewport(viewport);
        context->setConstant("u_Color", glm::vec4(x, y, 0.5f, 1.0f));

        context->setConstant("u_MVP", proj * view * model);

        renderer.draw(vertexBuffer, indexBuffer);

        renderer.endScene();

        if (x > 1.0f)
            increment = -0.05f;
        else if (x < 0.0f)
            increment = 0.05f;
        x += increment;

        if (y > 1.0f)
            increment = -0.05f;
        else if (y < 0.0f)
            increment = 0.05f;
        y += increment;

        window.swapBuffers();
    }
}