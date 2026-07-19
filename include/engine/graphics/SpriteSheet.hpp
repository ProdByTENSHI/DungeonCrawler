#pragma once

#include <string>
#include <spdlog/spdlog.h>
#include <raylib.h>

#include "engine/tenshiUtil/Types.hpp"
#include "engine/tenshiUtil/math/Vector2Int.hpp"

namespace tenshi
{
    class SpriteSheet
    {
    public:
        SpriteSheet(u32 id, u32 textureId, u32 fWidth, u32 fHeight);
        ~SpriteSheet();

        // Constructs a Source Rect for a Frame in the Spritesheet
        // 0,0 to MAX,MAX
        Rectangle GetSourceRect(const Vector2Int frame) const;

        u32 GetTexture() const { return m_TextureId; }

        u32 GetFrameWidth() const { return m_fWidth; }
        u32 GetFrameHeight() const { return m_fHeight; }

    public:
        const u32 m_Id;

    private:
        u32 m_TextureId;
        u32 m_fWidth = 16;
        u32 m_fHeight = 16;
    };
}