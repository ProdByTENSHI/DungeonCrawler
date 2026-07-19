#pragma once

#include "engine/tenshiUtil/Types.hpp"

namespace tenshi
{
    enum class KeyState : u8
    {
        Pressed,
        Released,
        Hold,
        None
    };

    struct KeyEvent
    {
        KeyEvent(i32 keyCode, KeyState state)
            : m_KeyCode(keyCode), m_State(state) {}

        i32 m_KeyCode = 0;
        KeyState m_State = KeyState::None;
    };

    struct MouseEvent
    {
        MouseEvent(i32 button, KeyState state)
            : m_Button(button), m_State(state)
        {
        }

        i32 m_Button = 0;
        KeyState m_State = KeyState::None;
    };
}