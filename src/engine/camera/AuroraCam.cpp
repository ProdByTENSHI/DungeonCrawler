#include "engine/camera/AuroraCam.hpp"

#include <raymath.h>

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    AuroraCam::AuroraCam()
    {
        m_Camera.zoom = m_Zoom;
        m_Camera.offset = {(f32)VIEWPORT_SIZE.x * 0.5f, (f32)VIEWPORT_SIZE.y * 0.5f};
        m_Camera.rotation = 0.0f;
    }


    void AuroraCam::ShakeCamera(f32 amount, u32 frames)
    {
        m_CurrentShakeFrame = 0;
        m_ShakeFrames = frames;
        m_ShakeAmount = amount;

        m_OriginalOffset = m_Camera.offset;
    }

    void AuroraCam::SetFollowTarget(Vector2* targetPos, Vector2 offset)
    {
        m_Camera.offset = {(f32)(VIEWPORT_SIZE.x * 0.5f) + offset.x,
            (f32)(VIEWPORT_SIZE.y * 0.5f) + offset.y};
        m_Target = targetPos;
        m_TargetOffset = offset;
    }

    void AuroraCam::Update()
    {
        FollowTarget();

        if (m_CurrentShakeFrame < m_ShakeFrames)
        {
            f32 _strength = m_ShakeAmount * (1 - ((f32)m_CurrentShakeFrame / (f32)m_ShakeFrames));

            m_Offset.x = cosf((f32)GetTime() * 90.0f) * _strength;
            m_Offset.y = cosf((f32)GetTime() * 180.0f) * _strength;

            ++m_CurrentShakeFrame;

            m_Camera.offset = Vector2Lerp(m_OriginalOffset,
                m_Offset, 15.0f * GetFrameTime());

            if (m_CurrentShakeFrame >= m_ShakeFrames)
            {
                m_Camera.offset = m_OriginalOffset;
            }
        }
    }

    void AuroraCam::FollowTarget()
    {
        if (m_Target == nullptr)
            return;

        f32 _t = 1.0f - (expf(-m_Smoothness * GetFrameTime()));

        m_Camera.target.x = lerp(m_Camera.target.x, m_Target->x, _t);
        m_Camera.target.y = lerp(m_Camera.target.y, m_Target->y, _t);

        // -- Bounds Check
        Vector2 _sectionSize = g_WorldManager->GetSectionSize();

        Vector2 _halfScreen = VIEWPORT_SIZE * 0.5f;
        f32 _xOffset = (m_Camera.offset.x - _halfScreen.x) / m_Camera.zoom;
        f32 _yOffset = (m_Camera.offset.y - _halfScreen.y) / m_Camera.zoom;

        float _minX = m_Camera.offset.x / m_Camera.zoom - _xOffset;
        float _minY = m_Camera.offset.y / m_Camera.zoom - _yOffset;
        float _maxX = _sectionSize.x - (_halfScreen.x / m_Camera.zoom) - _xOffset;
        float _maxY = _sectionSize.y - (_halfScreen.y / m_Camera.zoom) - _yOffset;

        m_Camera.target.x = std::clamp(m_Camera.target.x,
        _minX,
        _maxX);

        m_Camera.target.y = std::clamp(m_Camera.target.y,
        _minY,
         _maxY);
    }
}
