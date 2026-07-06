#pragma once

#include "engine/tenshiUtil/Types.hpp"

#include <raylib.h>

namespace tenshi
{
    // Player Constants
    constexpr f32 MOVEMENT_SPEED = 50.0f;
    constexpr f32 TIME_BETWEEN_SHOTS = 0.3f;
    constexpr f32 RELOAD_TIME = 1.3f;
    constexpr u16 MAG_CAPACITY = 25;

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

        u16 m_BulletsInMag = MAG_CAPACITY;
        f32 m_TimeSinceAttack = 0.0f;
        bool m_ShouldShoot = false;
        bool m_ShouldReload = false;

        // Can either be left or right
        PlayerDir m_LastFacingDirection = PlayerDir::Right;
    };
}
