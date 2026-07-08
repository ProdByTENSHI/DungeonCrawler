#pragma once
#include "EnemyState.hpp"

namespace tenshi
{
    class DroneDieState : public EnemyState
    {
    public:
        explicit DroneDieState(EnemyStates state = EnemyStates::Die);
        ~DroneDieState() {}

        void OnEntry(GenericEnemyData& data) override;
        void OnUpdate(GenericEnemyData& data) override;
        void OnExit(GenericEnemyData& data) override;
    };
}
