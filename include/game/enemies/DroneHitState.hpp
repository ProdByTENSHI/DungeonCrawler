#pragma once
#include "EnemyState.hpp"

namespace tenshi
{
    class DroneHitState : public EnemyState
    {
    public:
        explicit DroneHitState(EnemyStates state = EnemyStates::Hit);
        ~DroneHitState() {}

        void OnEntry(GenericEnemyData& data) override;
        void OnUpdate(GenericEnemyData& data) override;
        void OnExit(GenericEnemyData& data) override;
    };
}
