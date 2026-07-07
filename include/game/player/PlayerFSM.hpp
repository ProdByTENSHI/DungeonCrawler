#pragma once
#include "PlayerState.hpp"

#include <unordered_map>

namespace tenshi
{
    class PlayerFSM
    {
    public:
        PlayerFSM();
        ~PlayerFSM();

        void Update(PlayerData& data);
        void SetState(PlayerStates state, PlayerData& data);

        PlayerState* GetCurrentState() { return m_CurrentState; }
        PlayerStates GetCurrentStateType() const { return m_CurrentState->m_State;}

    private:
        std::unordered_map<PlayerStates, PlayerState*> m_StatesTable;

        PlayerState* m_CurrentState = nullptr;
    };
}
