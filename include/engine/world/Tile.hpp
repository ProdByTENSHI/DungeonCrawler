#pragma once

#include "engine/tenshiUtil/Types.hpp"
#include "engine/globals/Constants.hpp"

#include <raylib.h>

#include "engine/tenshiUtil/math/Vector2Int.hpp"

namespace tenshi
{
    // Data Tile
    struct Tile
    {
        // X,Y = 0 = Top Left
        Vector2Int m_Position = {0,0};

        // Is an Entity on the Tile
        bool m_IsOccupied = false;

        // true = Ground, false = Water
        bool m_IsSolid = true;

        u16 m_Padding1 = 0;

        Rectangle GetBounds() const
        {
            return {
                (f32)m_Position.x * TILE_SIZE,
                (f32)m_Position.y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE
            };
        }

        bool operator==(const Tile& rhs) const
        {
            return m_Position == rhs.m_Position;
        }
    };

    // Tile Data needed for Rendering a Tile
    struct RenderTile
    {
        Tile* m_TileData = nullptr;

        u32 m_TextureId = 0;

        Color m_Color = WHITE;

        Rectangle m_DstRect = {0};
        Rectangle m_SrcRect = {0};
    };
}
