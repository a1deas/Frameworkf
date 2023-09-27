#include "Core/log.h"
#include <iostream>
#include <format>

#include "Platform/platform.h"
#include "Platform/window.h"

#include "graphicsContext.h"

void init();
void update();

int main()
{
    Ff::Log      logger("Logger");
    Ff::Platform platform;
    Ff::Window   window(800, 600, "Frameworkf");
    std::unique_ptr<Ff::GraphicsContext> context = Ff::GraphicsContext::create(&window);

    init();

    while (!window.shouldClose())
    {
        platform.pollEvents();
        update();
        window.swapBuffers();
    }
}