#pragma once

#include "engine/tenshiUtil/Types.hpp"
#include "engine/tenshiUtil/eventsystem/EventSystem.h"

#include <raylib.h>
#include <queue>
#include "engine/input/InputEvents.hpp"

namespace tenshi
{
    inline Event<KeyEvent> OnKeyPressedEvent;
    inline Event<KeyEvent> OnKeyHoldEvent;
    inline Event<KeyEvent> OnKeyReleasedEvent;

    inline Event<> OnMouseMoveEvent;
    inline Event<MouseEvent> OnMousePressedEvent;
    inline Event<MouseEvent> OnMouseHoldEvent;
    inline Event<MouseEvent> OnMouseReleasedEvent;

    class InputManager
    {
    public:
        void UpdateInputEvents();

        Vector2 GetMouseWorldPosition() const;

    private:
        std::queue<KeyEvent> m_KeyQueue;
        std::queue<MouseEvent> m_MouseQueue;
    };
}
