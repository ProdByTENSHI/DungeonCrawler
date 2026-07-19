#include "engine/graphics/Sprite.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    Sprite::Sprite(u32 id, u32 spriteSheetId, Rectangle srcRect)
        : m_Id(id), m_SrcRect(srcRect)
    {
        m_SpriteSheet = g_RscManager->GetSpritesheet(spriteSheetId);
    }

    Sprite::Sprite(const Sprite& other)
        : m_Id(other.m_Id), m_SpriteSheet(other.m_SpriteSheet), m_SrcRect(other.m_SrcRect)
    {
    }
}
