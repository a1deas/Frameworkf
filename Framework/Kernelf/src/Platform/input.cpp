#include "input.h"

namespace Ff
{
    std::bitset<static_cast<glm::size_t>(MouseButton::LAST)> Input::m_MouseBitset;

    std::bitset<static_cast<size_t>(Key::KEY_LAST)> Input::m_KeyBitset;

    glm::vec2 Input::m_CursorPosition;

    glm::vec2 Input::m_MouseOffset;

    double Input::m_ScrollOffset;

} // namespace Ff