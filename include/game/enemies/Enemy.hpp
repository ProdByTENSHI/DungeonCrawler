#pragma once
#include "EnemyFSM.hpp"
#include "engine/entities/Entity.hpp"

namespace tenshi
{
    class Enemy : public Entity
    {
    public:
        Enemy(u32 id, const std::string& name = "Enemy");
        ~Enemy();

        void Update() override;
        RenderCommand CreateRenderCommand() override;

        Rectangle GetBoundingBox() const override;

    public:
        GenericEnemyData m_Data;

    protected:
        virtual EnemyStates ResolveState();
        void ResolveCollision();

    protected:
        EnemyFSM* m_FSM = nullptr;

        Vector2 m_Size = {32.0f, 32.0f};
        Vector2 m_BoundingBoxSize = {32.0f, 32.0f};
        Vector2 m_BoundingBoxOffset = {0.0f, 0.0f};
    };
}
