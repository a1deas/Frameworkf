#include "input.h"

namespace Ff
{
    std::bitset<static_cast<glm::size_t>(MouseButton::LAST)> Input::mouseBitset;

    std::bitset<static_cast<size_t>(Key::KEY_LAST)> Input::keyBitset;

    glm::vec2 Input::cursorPosition;
} // namespace Ff