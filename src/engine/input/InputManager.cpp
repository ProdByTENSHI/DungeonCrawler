#include "engine/input/InputManager.hpp"

namespace tenshi
{
    void InputManager::UpdateInputEvents()
    {
        // TODO: Implement Hold only after certain delay
        // Clear Queues from frame before
        std::queue<KeyEvent> m_EmptyKeyEventsQueue;
        std::swap(m_KeyQueue, m_EmptyKeyEventsQueue);

        std::queue<MouseEvent> m_EmptyMouseEventsQueue;
        std::swap(m_EmptyMouseEventsQueue, m_EmptyMouseEventsQueue);

        // Keyboard
        for (i32 key = KEY_NULL; key < KEY_KB_MENU; key++)
        {
            if (IsKeyPressed(key))
            {
                m_KeyQueue.push({key, KeyState::Pressed});
            }

            if (IsKeyDown(key))
            {
                m_KeyQueue.push({key, KeyState::Hold});
            }

            if (IsKeyReleased(key))
            {
                m_KeyQueue.push({key, KeyState::Released});
            }
        }

        // Mouse Buttons
        for (i32 button = 0; button < 3; button++)
        {
            if (IsMouseButtonPressed(button))
            {
                m_MouseQueue.push({MOUSE_BUTTON_LEFT, KeyState::Pressed});
            }

            if (IsMouseButtonReleased(button))
            {
                m_MouseQueue.push({MOUSE_BUTTON_LEFT, KeyState::Released});
            }

            if (IsMouseButtonDown(button))
            {
                m_MouseQueue.push({MOUSE_BUTTON_LEFT, KeyState::Hold});
            }
        }

        while (m_KeyQueue.size() > 0)
        {
            auto key = m_KeyQueue.front();

            switch (key.m_State)
            {
            case KeyState::Pressed:
                OnKeyPressed.Dispatch(key);
                break;

            case KeyState::Hold:
                OnKeyHold.Dispatch(key);
                break;

            case KeyState::Released:
                OnKeyReleased.Dispatch(key);
                break;

            case KeyState::None:
                break;
            }

            m_KeyQueue.pop();
        }

        while (m_MouseQueue.size() > 0)
        {
            auto mouseBtn = m_MouseQueue.front();

            switch (mouseBtn.m_State)
            {
            case KeyState::Pressed:
                OnMousePressed.Dispatch(mouseBtn);
                break;

            case KeyState::Hold:
                OnMouseHold.Dispatch(mouseBtn);
                break;

            case KeyState::Released:
                OnMouseReleased.Dispatch(mouseBtn);
                break;

            case KeyState::None:
                break;
            }

            m_MouseQueue.pop();
        }
    }
}