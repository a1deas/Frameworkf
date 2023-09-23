#include "framework.h"

using namespace Ff;
void init()
{

}

void update()
{
    if (Input::isKeyPressed(Key::KEY_ESCAPE))
    {
        glm::vec2 position = Input::getCursorPosition();
        FFINFO("Position: {}, {}", position.x, position.y);
    }
}