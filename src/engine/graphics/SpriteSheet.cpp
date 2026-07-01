#include "engine/graphics/SpriteSheet.hpp"

namespace tenshi
{
    SpriteSheet::SpriteSheet(u32 id, u32 textureId, u32 fWidth, u32 fHeight)
        : m_Id(id), m_TextureId(textureId), m_fWidth(fWidth), m_fHeight(fHeight)
    {
    }

    SpriteSheet::~SpriteSheet()
    {
    }

    Rectangle SpriteSheet::GetSourceRect(const Vector2Int frame) const
    {
        Rectangle _rect = {
            (f32)frame.x * m_fWidth, (f32)frame.y * m_fHeight,
            (f32)m_fWidth, (f32)m_fHeight
        };

        return _rect;
    }
}