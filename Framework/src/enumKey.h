#pragma once

#include <string>

namespace Ff
{
    enum class Key
    {
        KEY_UNKNOWN       = -1,
        KEY_SPACE         = 32,
        KEY_APOSTROPHE    = 39,
        KEY_COMMA         = 44,
        KEY_MINUS         = 45,
        KEY_PERIOD        = 46,
        KEY_SLASH         = 47,
        KEY_0             = 48,
        KEY_1             = 49,
        KEY_2             = 50,
        KEY_3             = 51,
        KEY_4             = 52,
        KEY_5             = 53,
        KEY_6             = 54,
        KEY_7             = 55,
        KEY_8             = 56,
        KEY_9             = 57,
        KEY_SEMICOLON     = 59,
        KEY_EQUAL         = 61,
        KEY_A             = 65,
        KEY_B             = 66,
        KEY_C             = 67,
        KEY_D             = 68,
        KEY_E             = 69,
        KEY_F             = 70,
        KEY_G             = 71,
        KEY_H             = 72,
        KEY_I             = 73,
        KEY_J             = 74,
        KEY_K             = 75,
        KEY_L             = 76,
        KEY_M             = 77,
        KEY_N             = 78,
        KEY_O             = 79,
        KEY_P             = 80,
        KEY_Q             = 81,
        KEY_R             = 82,
        KEY_S             = 83,
        KEY_T             = 84,
        KEY_U             = 85,
        KEY_V             = 86,
        KEY_W             = 87,
        KEY_X             = 88,
        KEY_Y             = 89,
        KEY_Z             = 90,
        KEY_LEFT_BRACKET  = 91,
        KEY_BACKSLASH     = 92,
        KEY_RIGHT_BRACKET = 93,
        KEY_GRAVE_ACCENT  = 96,
        KEY_WORLD_1       = 161,
        KEY_WORLD_2       = 162,
        KEY_ESCAPE        = 256,
        KEY_ENTER         = 257,
        KEY_TAB           = 258,
        KEY_BACKSPACE     = 259,
        KEY_INSERT        = 260,
        KEY_DELETE        = 261,
        KEY_RIGHT         = 262,
        KEY_LEFT          = 263,
        KEY_DOWN          = 264,
        KEY_UP            = 265,
        KEY_PAGE_UP       = 266,
        KEY_PAGE_DOWN     = 267,
        KEY_HOME          = 268,
        KEY_END           = 269,
        KEY_CAPS_LOCK     = 280,
        KEY_SCROLL_LOCK   = 281,
        KEY_NUM_LOCK      = 282,
        KEY_PRINT_SCREEN  = 283,
        KEY_PAUSE         = 284,
        KEY_F1            = 290,
        KEY_F2            = 291,
        KEY_F3            = 292,
        KEY_F4            = 293,
        KEY_F5            = 294,
        KEY_F6            = 295,
        KEY_F7            = 296,
        KEY_F8            = 297,
        KEY_F9            = 298,
        KEY_F10           = 299,
        KEY_F11           = 300,
        KEY_F12           = 301,
        KEY_F13           = 302,
        KEY_F14           = 303,
        KEY_F15           = 304,
        KEY_F16           = 305,
        KEY_F17           = 306,
        KEY_F18           = 307,
        KEY_F19           = 308,
        KEY_F20           = 309,
        KEY_F21           = 310,
        KEY_F22           = 311,
        KEY_F23           = 312,
        KEY_F24           = 313,
        KEY_F25           = 314,
        KEY_KP_0          = 320,
        KEY_KP_1          = 321,
        KEY_KP_2          = 322,
        KEY_KP_3          = 323,
        KEY_KP_4          = 324,
        KEY_KP_5          = 325,
        KEY_KP_6          = 326,
        KEY_KP_7          = 327,
        KEY_KP_8          = 328,
        KEY_KP_9          = 329,
        KEY_KP_DECIMAL    = 330,
        KEY_KP_DIVIDE     = 331,
        KEY_KP_MULTIPLY   = 332,
        KEY_KP_SUBTRACT   = 333,
        KEY_KP_ADD        = 334,
        KEY_KP_ENTER      = 335,
        KEY_KP_EQUAL      = 336,
        KEY_LEFT_SHIFT    = 340,
        KEY_LEFT_CONTROL  = 341,
        KEY_LEFT_ALT      = 342,
        KEY_LEFT_SUPER    = 343,
        KEY_RIGHT_SHIFT   = 344,
        KEY_RIGHT_CONTROL = 345,
        KEY_RIGHT_ALT     = 346,
        KEY_RIGHT_SUPER   = 347,
        KEY_MENU          = 348,

        KEY_LAST,
    };

    constexpr std::string_view getKeyString(Key m_key)
    {
        switch (m_key)
        {
            case Key::KEY_UNKNOWN:
                return "Unknown";
            case Key::KEY_SPACE:
                return "Space";
            case Key::KEY_APOSTROPHE:
                return "Apostrophe";
            case Key::KEY_COMMA:
                return "Comma";
            case Key::KEY_MINUS:
                return "Minus";
            case Key::KEY_PERIOD:
                return "Period";
            case Key::KEY_SLASH:
                return "Slash";
            case Key::KEY_0:
                return "Key 0";
            case Key::KEY_1:
                return "Key 1";
            case Key::KEY_2:
                return "Key 2";
            case Key::KEY_3:
                return "Key 3";
            case Key::KEY_4:
                return "Key 4";
            case Key::KEY_5:
                return "Key 5";
            case Key::KEY_6:
                return "Key 6";
            case Key::KEY_7:
                return "Key 7";
            case Key::KEY_8:
                return "Key 8";
            case Key::KEY_9:
                return "Key 9";
            case Key::KEY_SEMICOLON:
                return "Semicolon";
            case Key::KEY_EQUAL:
                return "Equal";
            case Key::KEY_A:
                return "A";
            case Key::KEY_B:
                return "B";
            case Key::KEY_C:
                return "C";
            case Key::KEY_D:
                return "D";
            case Key::KEY_E:
                return "E";
            case Key::KEY_F:
                return "F";
            case Key::KEY_G:
                return "G";
            case Key::KEY_H:
                return "H";
            case Key::KEY_I:
                return "I";
            case Key::KEY_J:
                return "J";
            case Key::KEY_K:
                return "K";
            case Key::KEY_L:
                return "L";
            case Key::KEY_M:
                return "M";
            case Key::KEY_N:
                return "N";
            case Key::KEY_O:
                return "O";
            case Key::KEY_P:
                return "P";
            case Key::KEY_Q:
                return "Q";
            case Key::KEY_R:
                return "R";
            case Key::KEY_S:
                return "S";
            case Key::KEY_T:
                return "T";
            case Key::KEY_U:
                return "U";
            case Key::KEY_V:
                return "V";
            case Key::KEY_W:
                return "W";
            case Key::KEY_X:
                return "X";
            case Key::KEY_Y:
                return "Y";
            case Key::KEY_Z:
                return "Z";
            case Key::KEY_LEFT_BRACKET:
                return "Left bracket";
            case Key::KEY_BACKSLASH:
                return "Backslash";
            case Key::KEY_RIGHT_BRACKET:
                return "Right bracket";
            case Key::KEY_GRAVE_ACCENT:
                return "Grave accent";
            case Key::KEY_WORLD_1:
                return "World 1";
            case Key::KEY_WORLD_2:
                return "World 2";
            case Key::KEY_ESCAPE:
                return "Escape";
            case Key::KEY_ENTER:
                return "Enter";
            case Key::KEY_TAB:
                return "Tab";
            case Key::KEY_BACKSPACE:
                return "Backspace";
            case Key::KEY_INSERT:
                return "Insert";
            case Key::KEY_DELETE:
                return "Delete";
            case Key::KEY_RIGHT:
                return "Right";
            case Key::KEY_LEFT:
                return "Left";
            case Key::KEY_DOWN:
                return "Down";
            case Key::KEY_UP:
                return "Up";
            case Key::KEY_PAGE_UP:
                return "Page up";
            case Key::KEY_PAGE_DOWN:
                return "Page down";
            case Key::KEY_HOME:
                return "Home";
            case Key::KEY_END:
                return "End";
            case Key::KEY_CAPS_LOCK:
                return "Caps lock";
            case Key::KEY_SCROLL_LOCK:
                return "Scroll lock";
            case Key::KEY_NUM_LOCK:
                return "Num lock";
            case Key::KEY_PRINT_SCREEN:
                return "Print screen";
            case Key::KEY_PAUSE:
                return "Pause";
            case Key::KEY_F1:
                return "F1";
            case Key::KEY_F2:
                return "F2";
            case Key::KEY_F3:
                return "F3";
            case Key::KEY_F4:
                return "F4";
            case Key::KEY_F5:
                return "F5";
            case Key::KEY_F6:
                return "F6";
            case Key::KEY_F7:
                return "F7";
            case Key::KEY_F8:
                return "F8";
            case Key::KEY_F9:
                return "F9";
            case Key::KEY_F10:
                return "F10";
            case Key::KEY_F11:
                return "F11";
            case Key::KEY_F12:
                return "F12";
            case Key::KEY_F13:
                return "F13";
            case Key::KEY_F14:
                return "F14";
            case Key::KEY_F15:
                return "F15";
            case Key::KEY_F16:
                return "F16";
            case Key::KEY_F17:
                return "F17";
            case Key::KEY_F18:
                return "F18";
            case Key::KEY_F19:
                return "F19";
            case Key::KEY_F20:
                return "F20";
            case Key::KEY_F21:
                return "F21";
            case Key::KEY_F22:
                return "F22";
            case Key::KEY_F23:
                return "F23";
            case Key::KEY_F24:
                return "F24";
            case Key::KEY_F25:
                return "F25";
            case Key::KEY_KP_0:
                return "KP_0";
            case Key::KEY_KP_1:
                return "KP_1";
            case Key::KEY_KP_2:
                return "KP_2";
            case Key::KEY_KP_3:
                return "KP_3";
            case Key::KEY_KP_4:
                return "KP_4";
            case Key::KEY_KP_5:
                return "KP_5";
            case Key::KEY_KP_6:
                return "KP_6";
            case Key::KEY_KP_7:
                return "KP_7";
            case Key::KEY_KP_8:
                return "KP_8";
            case Key::KEY_KP_9:
                return "KP_9";
            case Key::KEY_KP_DECIMAL:
                return "KP Decimal";
            case Key::KEY_KP_DIVIDE:
                return "KP Divide";
            case Key::KEY_KP_MULTIPLY:
                return "KP Multiply";
            case Key::KEY_KP_SUBTRACT:
                return "KP Subtract";
            case Key::KEY_KP_ADD:
                return "KP Add";
            case Key::KEY_KP_ENTER:
                return "KP Enter";
            case Key::KEY_KP_EQUAL:
                return "KP Equal";
            case Key::KEY_LEFT_SHIFT:
                return "Left shift";
            case Key::KEY_LEFT_CONTROL:
                return "Left control";
            case Key::KEY_LEFT_ALT:
                return "Left alt";
            case Key::KEY_LEFT_SUPER:
                return "Left super";
            case Key::KEY_RIGHT_SHIFT:
                return "Right shift";
            case Key::KEY_RIGHT_CONTROL:
                return "Right control";
            case Key::KEY_RIGHT_ALT:
                return "Right alt";
            case Key::KEY_RIGHT_SUPER:
                return "Right super";
            case Key::KEY_MENU:
                return "Unknown 2";
            default:
                return "Unknown 3";
        }
    }
} // namespace Ff