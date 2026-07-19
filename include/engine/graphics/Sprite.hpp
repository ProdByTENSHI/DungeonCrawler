#pragma once

#include "engine/graphics/SpriteSheet.hpp"
#include "engine/tenshiUtil/Types.hpp"

namespace tenshi
{
    struct Sprite
    {
        Sprite(u32 id, u32 spriteSheetId, Rectangle srcRect);
        Sprite(const Sprite& other);

        const u32 m_Id;

        SpriteSheet* m_SpriteSheet = nullptr;
        Rectangle m_SrcRect = {0, 0, 0, 0};
    };
}
