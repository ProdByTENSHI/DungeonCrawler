#include "engine/camera/AuroraCam.hpp"

#include <raymath.h>

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    AuroraCam::AuroraCam()
    {
        m_Camera.zoom = m_Zoom;
        m_Camera.offset = {(f32)RENDER_TEXTURE_SIZE.x * 0.5f, (f32)RENDER_TEXTURE_SIZE.y * 0.5f};
        m_Camera.rotation = 0.0f;
    }


    void AuroraCam::SetFollowTarget(Vector2* targetPos, Vector2 offset)
    {
        m_Camera.offset = {(f32)(RENDER_TEXTURE_SIZE.x * 0.5f) + offset.x,
            (f32)(RENDER_TEXTURE_SIZE.y * 0.5f) + offset.y};
        m_Target = targetPos;
    }

    void AuroraCam::Update()
    {
        // TODO: Keep Camera in Bounds

        FollowTarget();
    }

    void AuroraCam::FollowTarget()
    {
        if (m_Target == nullptr)
            return;

        m_Camera.target.x = lerp(m_Camera.target.x, m_Target->x, m_FollowSpeed * GetFrameTime());
        m_Camera.target.y = lerp(m_Camera.target.y, m_Target->y, m_FollowSpeed * GetFrameTime());
    }
}
