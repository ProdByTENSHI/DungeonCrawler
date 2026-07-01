#pragma once

#include "engine/tenshiUtil/Types.hpp"
#include "engine/tenshiUtil/eventsystem/EventSystem.h"

#include <raylib.h>
#include <queue>

namespace tenshi
{
    typedef struct KeyEvent;
    typedef struct MouseEvent;

    inline Event<KeyEvent> OnKeyPressed;
    inline Event<KeyEvent> OnKeyHold;
    inline Event<KeyEvent> OnKeyReleased;

    inline Event<> OnMouseMove;
    inline Event<MouseEvent> OnMousePressed;
    inline Event<MouseEvent> OnMouseHold;
    inline Event<MouseEvent> OnMouseReleased;

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

    class InputManager
    {
    public:
        void UpdateInputEvents();

    private:
        std::queue<KeyEvent> m_KeyQueue;
        std::queue<MouseEvent> m_MouseQueue;
    };
}
