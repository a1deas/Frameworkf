#include "Core/log.h"
#include <iostream>
#include <format>

#include "Platform/platform.h"
#include "Platform/window.h"

#include "graphicsContext.h"
#include "Shader/shaderProgram.h"
#include "Buffer/vertexBuffer.h"

using namespace Ff;

void init();
void update();

int main()
{
    Log                              logger("Logger");
    Platform                         platform;
    Window                           window(800, 600, "Frameworkf");
    std::unique_ptr<GraphicsContext> context = GraphicsContext::create(&window);

    ShaderProgramSpec spec;
    spec.vertexShaderPath   = "Framework/Shaders/testVS.glsl";
    spec.fragmentShaderPath = "Framework/Shaders/testFS.glsl";

    std::shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::create(spec);

    init();

    while (!window.shouldClose())
    {
        platform.pollEvents();
        update();

        context->useProgram(shaderProgram);
        
        window.swapBuffers();
    }
}