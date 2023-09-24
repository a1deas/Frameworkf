#include "Core/log.h"
#include <iostream>
#include <format>

#include "Platform/platform.h"
#include "Platform/window.h"

void init();
void update();

int main()
{
    Ff::Log      logger("Logger");
    Ff::Platform platform;
    Ff::Window   window(800, 600, "Frameworkf");

    init();

    while (!window.shouldClose())
    {
        platform.pollEvents();
        update();
        window.swapBuffers();
    }
}