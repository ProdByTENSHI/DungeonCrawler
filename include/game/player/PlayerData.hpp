#pragma once

#include "engine/tenshiUtil/Types.hpp"

#include <raylib.h>

namespace tenshi
{
    // Player Constants
    const f32 MOVEMENT_SPEED = 50.0f;

    enum class PlayerDir : u8
    {
        Up,
        Down,
        Left,
        Right
    };

    struct PlayerData
    {
        Vector2 m_Position = {0,0};
        Vector2 m_Velocity = {0,0};
        Vector2 m_Scale = {1,1};
        PlayerDir m_Direction = PlayerDir::Right;
        bool m_IsMoving = false;
    };
}
