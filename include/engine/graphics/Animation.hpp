#pragma once
#include "engine/tenshiUtil/Types.hpp"
#include "engine/render/RenderCommand.hpp"

#include <vector>
#include <raylib.h>

namespace tenshi
{
    struct Animation
    {
        Animation(u32 spriteSheetId, f32 interval, std::vector<Rectangle> frames);
        ~Animation();

        RenderCommand GetRenderCommand() const;
        void Update();

        u32 m_SpriteSheetId = 0;
        f32 m_Interval = 0.1f;
        std::vector<Rectangle> m_Frames;
        u32 m_CurrentFrame = 0;

    private:
        u32 m_TextureId;
        f32 m_TimeSinceLastFrame = 0.0f;
    };
}