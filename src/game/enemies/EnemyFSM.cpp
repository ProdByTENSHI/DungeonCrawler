#include "game/enemies/EnemyFSM.hpp"

#include "spdlog/spdlog.h"

namespace tenshi
{
    EnemyFSM::EnemyFSM()
    {
    }

    EnemyFSM::~EnemyFSM()
    {
    }

    void EnemyFSM::Update(GenericEnemyData& data)
    {
        if (!m_CurrentState)
            return;

        m_CurrentState->OnUpdate(data);
    }

    void EnemyFSM::SetState(EnemyStates state, GenericEnemyData& data)
    {
        if (m_CurrentState != nullptr && m_CurrentState->m_State == state)
            return;

        if (m_CurrentState != nullptr)
            m_CurrentState->OnExit(data);

        m_CurrentState = m_StatesTable[state];
        if (!m_CurrentState)
            spdlog::error("Player State {} not in Table", (u8)state);
        m_CurrentState->OnEntry(data);
    }

    void EnemyFSM::AddState(EnemyStates state, EnemyState* obj)
    {
        m_StatesTable.insert({state, obj});
    }
}
