#include "game/enemies/DroneHitState.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    DroneHitState::DroneHitState(EnemyStates state)
        : EnemyState(state)
    {
        m_Anim = g_RscManager->GetAnimation(Animations::Drone_Hit);
    }

    void DroneHitState::OnEntry(GenericEnemyData& data)
    {
        EnemyState::OnEntry(data);
    }

    void DroneHitState::OnUpdate(GenericEnemyData& data)
    {
        EnemyState::OnUpdate(data);
    }

    void DroneHitState::OnExit(GenericEnemyData& data)
    {
    }
}
