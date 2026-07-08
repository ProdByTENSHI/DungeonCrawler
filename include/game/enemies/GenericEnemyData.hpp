#pragma once

#include "engine/tenshiUtil/Types.hpp"

#include <raylib.h>

namespace tenshi
{
    struct GenericEnemyData
    {
        u32 m_Id = 0;

        Vector2 m_Position = {0.0f, 0.0f};
        Vector2 m_Velocity = Vector2(0.0f, 0.0f);
        f32 m_Range = 5.0f;
        f32 m_SeekRadius = 20.0f;

        u32 m_Health = 100;

        bool m_Shoot = false;

        bool m_WasHit = false;
    };
}
