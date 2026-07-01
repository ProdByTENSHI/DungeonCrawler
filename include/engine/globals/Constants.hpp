#pragma once

#include "engine/tenshiUtil/Types.hpp"

#include <raylib.h>

namespace tenshi
{
    constexpr f32 TILE_SIZE = 32.0f;
    const Vector2 VIEWPORT_SIZE = Vector2(480,320);

    enum class RenderLayer : u8
    {
        Ground,
        Collision,
        Entity,

        Last
    };
}