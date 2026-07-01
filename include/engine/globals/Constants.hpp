#pragma once

#include "engine/tenshiUtil/Types.hpp"

namespace tenshi
{
    constexpr f32 TILE_SIZE = 32.0f;

    enum class RenderLayer : u8
    {
        Ground,
        Water,
        Entity,

        Last
    };
}