#include "game/player/PlayerStateMachine.hpp"
#include "game/player/PlayerIdleState.hpp"
#include "game/player/PlayerRunState.hpp"
#include "game/player/PlayerShootState.hpp"

#include <spdlog/spdlog.h>

#include "game/player/PlayerReloadState.hpp"

namespace tenshi
{
    PlayerStateMachine::PlayerStateMachine()
    {
        // -- Initialize States Table
        m_StatesTable[PlayerStates::Idle] = new PlayerIdleState();
        m_StatesTable[PlayerStates::Run] = new PlayerRunState();
        m_StatesTable[PlayerStates::Shoot] = new PlayerShootState();
        m_StatesTable[PlayerStates::Reload]= new PlayerReloadState();
    }

    PlayerStateMachine::~PlayerStateMachine()
    {
    }

    void PlayerStateMachine::Update(PlayerData& data)
    {
        m_CurrentState->OnUpdate(data);
    }

    void PlayerStateMachine::SetState(PlayerStates state, PlayerData& data)
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
}
