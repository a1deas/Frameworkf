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
        Input() = delete;

        /** Sets mouse and scroll offsets to 0. */
        static void resetOffsets()
        {
            m_MouseOffset = { 0.0f, 0.0f };
            m_ScrollOffset = 0.0;
        }

        /** @return true if specified key is pressed. */
        static bool isKeyPressed(Key key)
        {
            return m_KeyBitset[static_cast<size_t>(key)];
        }

        /** @return true if specified button is pressed. */
        static bool isButtonPressed(MouseButton button)
        {
            return m_MouseBitset[static_cast<size_t>(button)];
        }

        /** Returns cursor position. */
        static glm::vec2 getCursorPosition()
        {
            return m_CursorPosition;
        }
        /** Returns mouse offset. */
        static glm::vec2 getMouseOffset() { return m_MouseOffset; }
        /** Returns scroll offset. */
        static double getScrollOffset() { return m_ScrollOffset; }

    private:
        static void setScrollOffset(double val) { m_ScrollOffset = val; }

        static void setButtonState(MouseButton button, bool state)
        {
            m_MouseBitset[static_cast<size_t>(button)] = state;
        }

        static void setKeyState(Key key, bool state)
        {
            m_KeyBitset[static_cast<size_t>(key)] = state;
        }

        static void setCursorPosition(glm::vec2 cursorPos)
        {
            glm::vec2 oldPos = m_CursorPosition;
            m_CursorPosition = cursorPos;
            m_MouseOffset = cursorPos - oldPos;
        }

    private:
        static std::bitset<static_cast<size_t>(MouseButton::LAST)> m_MouseBitset;
        static std::bitset<static_cast<size_t>(Key::KEY_LAST)> m_KeyBitset;
        static glm::vec2 m_CursorPosition;
        static glm::vec2 m_MouseOffset;
        static double m_ScrollOffset;
    };
} // namespace Ff