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

        void SetFollowTarget(Vector2* targetPos);
        void Update();

    public:
        Camera2D m_Camera;
        f32 m_Zoom = 1.75f;

        // -- Cam Follow
        f32 m_FollowSpeed = 10.0f;

    private:
        void FollowTarget();

    private:
        Vector2* m_Target;
    };
}
