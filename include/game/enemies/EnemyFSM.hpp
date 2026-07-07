#pragma once

#include "EnemyState.hpp"
#include "game/enemies/GenericEnemyData.hpp"
#include "engine/tenshiUtil/Types.hpp"

#include <map>

namespace tenshi
{
    class EnemyFSM
    {
    public:
        EnemyFSM();
        ~EnemyFSM();

        void Update(GenericEnemyData& data);
        void SetState(EnemyStates state, GenericEnemyData& data);

        void AddState(EnemyStates state, EnemyState* obj);

        EnemyState* GetCurrentState() { return m_CurrentState; }
        EnemyStates GetCurrentStateType() const { return m_CurrentState->m_State; }

    private:
        std::map<EnemyStates, EnemyState*> m_StatesTable;
        EnemyState* m_CurrentState = nullptr;
    };
}
