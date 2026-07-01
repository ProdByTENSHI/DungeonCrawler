#include "game/player/PlayerInput.hpp"

#include "engine/input/InputManager.hpp"

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

        OnKeyHold.Subscribe(OnKeyDown);
        OnKeyReleased.Subscribe(OnKeyUp);
    }

    PlayerInput::~PlayerInput()
    {
        OnKeyHold.Unsubscribe(OnKeyDown);
        OnKeyReleased.Unsubscribe(OnKeyUp);
    }

    void PlayerInput::HandleData(PlayerData& data)
    {
        data.m_Velocity = m_Data.m_Velocity;
    }
}
