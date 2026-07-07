#pragma once
#include "raylib.h"
#include "engine/tenshiUtil/Types.hpp"

namespace tenshi
{
    namespace player_constants
    {
        constexpr f32 WALK_SPEED = 10.0f;
        constexpr f32 RUN_SPEED = 25.0f;

        const Vector2 SIZE = {32.0f, 32.0f};
        const Vector2 BOUNDING_BOX_SIZE = {10.0f, 16.0f};
        const Vector2 BOUNDING_BOX_OFFSET = {12.0f, 16.0f};
    }
}
