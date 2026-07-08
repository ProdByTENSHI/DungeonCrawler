#include "game/enemies/DroneDieState.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    DroneDieState::DroneDieState(EnemyStates state)
        : EnemyState(state)
    {
        m_Anim = g_RscManager->GetAnimation(Animations::Drone_Die);
    }

    void DroneDieState::OnEntry(GenericEnemyData& data)
    {
        EnemyState::OnEntry(data);
    }

    void DroneDieState::OnUpdate(GenericEnemyData& data)
    {
        EnemyState::OnUpdate(data);
    }

    void DroneDieState::OnExit(GenericEnemyData& data)
    {
    }
}
