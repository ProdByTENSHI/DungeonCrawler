#pragma once

#include "engine/globals/Constants.hpp"

#include <raylib.h>

namespace tenshi
{
    // Holds all Data for Rendering something to the Screen
    struct RenderCommand {
        u32 m_TextureId = 0;
        f32 m_Rotation = 0.0f;
        Rectangle m_SrcRect;    // Pass w and h of texture for whole tex
        Rectangle m_DstRect;

        Color m_Color = WHITE;

        // Higher Orders are rendered later
        u8 m_RenderOrder = 0;

        // Used for std:: algorithms
        bool operator<(const RenderCommand &other) const noexcept {
            return m_TextureId < other.m_TextureId;
        }

        RenderCommand& operator=(const RenderCommand& rhs) {
            m_TextureId = rhs.m_TextureId;
            m_SrcRect = rhs.m_SrcRect;
            m_DstRect  = rhs.m_DstRect;

            return *this;
        }
    };
}