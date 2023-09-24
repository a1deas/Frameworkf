#pragma once

#include <bitset>
#include <glm/glm.hpp>

#include "enumButton.h"
#include "enumKey.h"

namespace Ff
{
    class Input
    {
        friend class Window;

    public:
        Input()
        {
        }

        static bool isKeyPressed(Key key)
        {
            return keyBitset[static_cast<size_t>(key)];
        }

        static bool isButtonPressed(MouseButton button)
        {
            return mouseBitset[static_cast<size_t>(button)];
        }

        static glm::vec2 getCursorPosition()
        {
            return cursorPosition;
        }

    private:
        static void setButtonState(MouseButton button, bool state)
        {
            mouseBitset[static_cast<size_t>(button)] = state;
        }

        static void setKeyState(Key key, bool state)
        {
            keyBitset[static_cast<size_t>(key)] = state;
        }

        static void setCursorPosition(glm::vec2 cursorPos)
        {
            cursorPosition = cursorPos;
        }

        static std::bitset<static_cast<size_t>(MouseButton::LAST)> mouseBitset;
        static std::bitset<static_cast<size_t>(Key::KEY_LAST)>     keyBitset;
        static glm::vec2                                           cursorPosition;
    };
} // namespace Ff