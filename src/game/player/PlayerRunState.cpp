#include "game/player/PlayerRunState.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    PlayerRunState::PlayerRunState()
        :  PlayerState(PlayerStates::Run)
    {
        // -- Initialize Animations
        m_Anim[PlayerDir::Right] = g_RscManager->GetAnimation(Animations::Player_Run);
    }

    PlayerRunState::~PlayerRunState()
    {
    }

    void PlayerRunState::OnEntry(PlayerData& data)
    {
        PlayerState::OnEntry(data);
    }

    void PlayerRunState::OnUpdate(PlayerData& data)
    {
        PlayerState::OnUpdate(data);
    }

    void PlayerRunState::OnExit(PlayerData& data)
    {
    }
}
