#include "game/enemies/DroneIdleState.hpp"

#include "engine/globals/Globals.hpp"
#include "engine/memory/RscManager.hpp"

namespace tenshi
{
    DroneIdleState::DroneIdleState(EnemyStates state)
        : EnemyState(state)
    {
        m_Anim = g_RscManager->GetAnimation(Animations::Drone_Idle);
    }

    void DroneIdleState::OnEntry(GenericEnemyData& data)
    {
        EnemyState::OnEntry(data);
    }

    void DroneIdleState::OnUpdate(GenericEnemyData& data)
    {
        EnemyState::OnUpdate(data);
    }

    void DroneIdleState::OnExit(GenericEnemyData& data)
    {
    }
}
