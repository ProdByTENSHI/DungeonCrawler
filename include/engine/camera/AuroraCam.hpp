#pragma once

#include <raylib.h>

#include "engine/tenshiUtil/Types.hpp"

namespace tenshi
{
    class AuroraCam
    {
    public:
        AuroraCam();
        ~AuroraCam() {}

        // Shakes the Camera with Amount and decays to zero in frames Frames
        void ShakeCamera(f32 amount, u32 frames);

        void SetFollowTarget(Vector2* targetPos, Vector2 offset);
        void Update();

    public:
        Camera2D m_Camera;
        f32 m_Zoom = 1.75f;

        // -- Cam Follow
        f32 m_FollowSpeed = 10.0f;
        f32 m_Smoothness = 2.2f;

    private:
        void FollowTarget();

    private:
        Vector2* m_Target = nullptr;
        Vector2 m_TargetOffset;

        u32 m_ShakeFrames = 0;
        u32 m_CurrentShakeFrame = 0;
        f32 m_ShakeAmount = 1.0f;
        f32 m_ShakeDecay = 1.0f;
        Vector2 m_Offset = {0.0f, 0.0f};
        Vector2 m_OriginalOffset = {0.0f, 0.0f};
    };
}
