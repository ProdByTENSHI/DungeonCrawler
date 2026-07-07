#include "game/enemies/Drone.hpp"

#include "game/enemies/DroneIdleState.hpp"

namespace tenshi
{
    Drone::Drone(u32 id, const std::string& name)
        : Enemy(id, name)
    {
        m_BoundingBoxSize = {12.0f, 32.0f};
        m_BoundingBoxOffset = {4.0f, 0.0f};

        m_FSM->AddState(EnemyStates::Idle, new DroneIdleState());

        m_FSM->SetState(EnemyStates::Idle, m_Data);
    }

    Drone::~Drone()
    {
    }

    void Drone::Update()
    {
        Enemy::Update();
    }

    RenderCommand Drone::CreateRenderCommand()
    {
        return Enemy::CreateRenderCommand();
    }
}
