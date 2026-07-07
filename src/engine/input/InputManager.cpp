#include "engine/input/InputManager.hpp"

#include "engine/globals/Constants.hpp"
#include "engine/globals/Globals.hpp"
#include "spdlog/spdlog.h"

namespace tenshi
{
    void InputManager::UpdateInputEvents()
    {
        // TODO: Implement Hold only after certain delay
        // Clear Queues from frame before
        m_KeyQueue = {};
        m_MouseQueue = {};

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
                m_MouseQueue.push({button, KeyState::Pressed});
            }

            if (IsMouseButtonReleased(button))
            {
                m_MouseQueue.push({button, KeyState::Released});
            }

            if (IsMouseButtonDown(button))
            {
                m_MouseQueue.push({button, KeyState::Hold});
            }
        }

        while (m_KeyQueue.size() > 0)
        {
            auto key = m_KeyQueue.front();

            switch (key.m_State)
            {
            case KeyState::Pressed:
                OnKeyPressedEvent.Dispatch(key);
                break;

            case KeyState::Hold:
                OnKeyHoldEvent.Dispatch(key);
                break;

            case KeyState::Released:
                OnKeyReleasedEvent.Dispatch(key);
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
                OnMousePressedEvent.Dispatch(mouseBtn);
                break;

            case KeyState::Hold:
                OnMouseHoldEvent.Dispatch(mouseBtn);
                break;

            case KeyState::Released:
                OnMouseReleasedEvent.Dispatch(mouseBtn);
                break;

            case KeyState::None:
                break;
            }

            m_MouseQueue.pop();
        }
    }

    Vector2 InputManager::GetMouseWorldPosition() const
    {
        Vector2 _pos = GetMousePosition();

        _pos.x /= g_MasterRenderer->m_RenderScaling.x;
        _pos.y /= g_MasterRenderer->m_RenderScaling.y;

        _pos = GetScreenToWorld2D(_pos, g_MainCam->m_Camera);

        return _pos;
    }
}
