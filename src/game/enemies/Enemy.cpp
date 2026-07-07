#include "game/enemies/Enemy.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    Enemy::Enemy(u32 id, const std::string& name)
        : Entity(id, name)
    {
        m_FSM = new EnemyFSM();
    }

    Enemy::~Enemy()
    {
    }

    void Enemy::Update()
    {
        m_FSM->Update(m_Data);

        EnemyStates _nextState = ResolveState();
        m_FSM->SetState(_nextState, m_Data);

        m_Data.m_Position.x += m_Data.m_Velocity.x * GetFrameTime();
        m_Data.m_Position.y += m_Data.m_Velocity.y * GetFrameTime();

        m_Position = m_Data.m_Position;
    }

    RenderCommand Enemy::CreateRenderCommand()
    {
        DrawRectGizmo(GetBoundingBox(), GREEN);
        RenderCommand _cmd;

        _cmd = m_FSM->GetCurrentState()->m_Anim->GetRenderCommand();
        _cmd.m_DstRect = {m_Position.x, m_Position.y, m_Size.x, m_Size.y};

        return _cmd;
    }

    Rectangle Enemy::GetBoundingBox() const
    {
        Rectangle _box;
        _box.x = m_Position.x + m_BoundingBoxOffset.x;
        _box.y = m_Position.y + m_BoundingBoxOffset.y;
        _box.width = m_Size.x;
        _box.height = m_Size.y;

        return _box;
    }

    EnemyStates Enemy::ResolveState()
    {
        return m_FSM->GetCurrentStateType();
    }

    void Enemy::ResolveCollision()
    {
        // -- Wall Collision --
        Rectangle _boundingBox = GetBoundingBox();
        std::vector<Rectangle> _colliders;
        bool _hasCollided = g_WorldManager->CheckCollision(_boundingBox, &_colliders);

        for (i32 i = 0; i < _colliders.size(); i++)
        {
            // Calculate overlap depths
            float overlapX = (_boundingBox.width + _colliders[i].width) / 2 - fabs(_boundingBox.x - _colliders[i].x);
            float overlapY = (_boundingBox.height + _colliders[i].height) / 2 - fabs(_boundingBox.y - _colliders[i].y);

            // Resolve on the axis with the smallest overlap
            if (overlapX < overlapY) {
                // Horizontal collision
                if (_boundingBox.x < _colliders[i].x) _boundingBox.x -= overlapX;
                else _boundingBox.x += overlapX;
                m_Data.m_Position.x -= m_Data.m_Velocity.x * GetFrameTime();
                m_Data.m_Velocity.x = 0;
            } else if (overlapX >= overlapY) {
                // Vertical collision
                if (_boundingBox.y < _colliders[i].y) _boundingBox.y -= overlapY;
                else _boundingBox.y += overlapY;
                m_Data.m_Position.y -= m_Data.m_Velocity.y * GetFrameTime();
                m_Data.m_Velocity.y = 0;
            }
        }
    }
}
