#pragma once

#include "engine/tenshiUtil/Types.hpp"

#include <raylib.h>

namespace tenshi
{
    // Data Tile
    struct Tile
    {
        // X,Y = 0 = Top Left
        Vector2 m_Position = {0,0};

        // Is an Entity on the Tile
        bool m_IsOccupied = false;

        // true = Ground, false = Water
        bool m_IsSolid = true;

        // Can Player move to this Tile
        bool m_IsValid = true;

        u8 m_Padding1 = 0;
    };

    // Tile Data needed for Rendering a Tile
    struct RenderTile
    {
        Tile* m_TileData = nullptr;

        u32 m_TextureId = 0;

        Rectangle m_DstRect = {0};
        Rectangle m_SrcRect = {0};

        u32 m_Padding1 = 0;
    };
}