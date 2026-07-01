#include "game/player/PlayerIdleState.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    PlayerIdleState::PlayerIdleState()
        :  PlayerState(PlayerStates::Idle)
    {
        // -- Initialize Animations
        m_Anim[PlayerDir::Right] = g_RscManager->GetAnimation(Animations::Player_Idle);
    }

    PlayerIdleState::~PlayerIdleState()
    {
    }

    void PlayerIdleState::OnEntry(PlayerData& data)
    {
    }

    void PlayerIdleState::OnUpdate(PlayerData& data)
    {
        PlayerState::OnUpdate(data);
    }

    void PlayerIdleState::OnExit(PlayerData& data)
    {
    }
}
