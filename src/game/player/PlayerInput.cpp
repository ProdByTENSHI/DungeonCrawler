#include "game/player/PlayerInput.hpp"

#include "engine/input/InputManager.hpp"
#include "spdlog/spdlog.h"

namespace tenshi
{
    PlayerInput::PlayerInput()
    {
        OnKeyDown = EventHandler<KeyEvent>([this](KeyEvent e)
        {
            switch (e.m_KeyCode)
            {
            default:
                return;

            case KEY_W:
                m_Data.m_Velocity.y = -MOVEMENT_SPEED;
                break;

            case KEY_S:
                m_Data.m_Velocity.y = MOVEMENT_SPEED;
                break;

            case KEY_A:
                m_Data.m_Velocity.x = -MOVEMENT_SPEED;
                break;

            case KEY_D:
                m_Data.m_Velocity.x = MOVEMENT_SPEED;
                break;

            case KEY_R:
                if (m_Data.m_BulletsInMag == MAG_CAPACITY)
                    break;

                m_Data.m_ShouldReload = true;
                break;
            }
        });

        OnKeyUp = EventHandler<KeyEvent>([this](KeyEvent e)
        {
            switch (e.m_KeyCode)
            {
            default:
                return;

            case KEY_W:
                m_Data.m_Velocity.y = 0.0f;
                break;

            case KEY_S:
                m_Data.m_Velocity.y = 0.0f;
                break;

            case KEY_A:
                m_Data.m_Velocity.x = 0.0f;
                break;

            case KEY_D:
                m_Data.m_Velocity.x = 0.0f;
                break;
            }
        });

        OnMouseDown = EventHandler<MouseEvent>([this](MouseEvent e)
        {
            switch (e.m_Button)
            {
            case MOUSE_BUTTON_LEFT:
                if (m_Data.m_BulletsInMag <= 0)
                {
                    OnReload.Dispatch();
                    break;
                }

                OnShoot.Dispatch();
                break;
            }
        });

        OnKeyHoldEvent.Subscribe(OnKeyDown);
        OnKeyReleasedEvent.Subscribe(OnKeyUp);
        OnMousePressedEvent.Subscribe(OnMouseDown);
    }

    PlayerInput::~PlayerInput()
    {
        OnKeyHoldEvent.Unsubscribe(OnKeyDown);
        OnKeyReleasedEvent.Unsubscribe(OnKeyUp);
    }

    void PlayerInput::HandleData(PlayerData& data)
    {
        data.m_Velocity = m_Data.m_Velocity;
    }
}
