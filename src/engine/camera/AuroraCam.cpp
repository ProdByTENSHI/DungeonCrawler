#include "engine/camera/AuroraCam.hpp"

#include <raymath.h>

namespace tenshi
{
    AuroraCam::AuroraCam()
    {
        m_Camera.zoom = m_Zoom;
        m_Camera.offset = {0.0f, 0.0f};
        m_Camera.rotation = 0.0f;
    }


    void AuroraCam::SetFollowTarget(Vector2* targetPos)
    {
    }

    void AuroraCam::Update()
    {
        FollowTarget();
    }

    void AuroraCam::FollowTarget()
    {
        if (!m_Target)
            return;

        m_Camera.target.x = lerp(m_Camera.target.x, m_Target->x, m_FollowSpeed * GetFrameTime());
        m_Camera.target.y = lerp(m_Camera.target.y, m_Target->y, m_FollowSpeed * GetFrameTime());
    }
}
