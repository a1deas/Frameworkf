#pragma once

#include <string>

namespace Ff
{
    enum class MouseButton
    {
        LEFT    = 0,
        RIGHT   = 1,
        MIDDLE  = 2,
        BACK    = 3,
        FORWARD = 4,
        LAST,
    };

    constexpr std::string_view getButtonString(MouseButton m_button)
    {
        switch (m_button)
        {
            case Ff::MouseButton::LEFT:
                return "Left";
            case Ff::MouseButton::RIGHT:
                return "Right";
            case Ff::MouseButton::MIDDLE:
                return "Middle";
            case Ff::MouseButton::BACK:
                return "Back";
            case Ff::MouseButton::FORWARD:
                return "Forward";
            case Ff::MouseButton::LAST:
                return "Last";
            default:
                return "Unknown";
        }
    }
} // namespace Ff