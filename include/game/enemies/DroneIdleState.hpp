#pragma once
#include "EnemyState.hpp"

namespace tenshi
{
    class DroneIdleState : public EnemyState
    {
    public:
        explicit DroneIdleState(EnemyStates state = EnemyStates::Idle);
        ~DroneIdleState() {}

        void OnEntry(GenericEnemyData& data) override;
        void OnUpdate(GenericEnemyData& data) override;
        void OnExit(GenericEnemyData& data) override;
    };
}
