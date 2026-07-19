#include "game/enemies/Drone.hpp"

#include "engine/globals/Globals.hpp"
#include "game/enemies/DroneDieState.hpp"
#include "game/enemies/DroneHitState.hpp"
#include "game/enemies/DroneIdleState.hpp"
#include "spdlog/spdlog.h"

namespace tenshi
{
    Drone::Drone(u32 id, const std::string& name)
        : Enemy(id, name)
    {
        m_BoundingBoxSize = {16.0f, 16.0f};
        m_BoundingBoxOffset = {5.0f, 3.0f};

        m_FSM->AddState(EnemyStates::Idle, new DroneIdleState());
        m_FSM->AddState(EnemyStates::Hit, new DroneHitState());
        m_FSM->AddState(EnemyStates::Die, new DroneDieState());

        m_FSM->SetState(EnemyStates::Idle, m_Data);

        m_Data.m_Health = 5;
    }

    Drone::~Drone()
    {
    }

    void Drone::Die()
    {
        Enemy::Die();
    }

    void Drone::Hit(u32 damage)
    {
        m_Data.m_WasHit = true;
        Enemy::Hit(damage);
        spdlog::info("Drone was damaged. New HP {}", m_Data.m_Health);
    }

    void Drone::Update()
    {
        Enemy::Update();
    }

    RenderCommand Drone::CreateRenderCommand()
    {
        return Enemy::CreateRenderCommand();
    }

    Rectangle Drone::GetBoundingBox() const
    {
        Rectangle _box = Enemy::GetBoundingBox();
        _box.x += m_BoundingBoxOffset.x;
        _box.y += m_BoundingBoxOffset.y;
        _box.width = m_BoundingBoxSize.x;
        _box.height = m_BoundingBoxSize.y;

        return _box;
    }

    EnemyStates Drone::ResolveState()
    {
        EnemyStates _currentState = m_FSM->GetCurrentStateType();
        switch (_currentState)
        {
        case EnemyStates::Idle:
            if (m_Data.m_WasHit)
            {
                m_Data.m_WasHit = false;
                return EnemyStates::Hit;
            }

            if (m_Data.m_Health <= 0)
            {
                return EnemyStates::Die;
            }
            break;

        case EnemyStates::Hit:
            if (m_FSM->GetCurrentState()->HasAnimFinished(m_Data))
            {
                if (m_Data.m_Health <= 0)
                {
                    return EnemyStates::Die;
                }

                if (m_Data.m_Velocity.x <= 0.1f && m_Data.m_Velocity.y <= 0.1f)
                {
                    return EnemyStates::Idle;
                }
            }
            break;

        case EnemyStates::Die:
            if (m_FSM->GetCurrentState()->HasAnimFinished(m_Data))
            {
                g_EntityManager->DestroyEntity(*this);
            }
            break;

        default:
            spdlog::info("Enemy State {} is not implemented", (u8)_currentState);
            break;
        }

        return _currentState;
    }
}
