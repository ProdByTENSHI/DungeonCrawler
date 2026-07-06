#include "game/player/PlayerReloadState.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    PlayerReloadState::PlayerReloadState()
        :  PlayerState(PlayerStates::Reload)
    {
        // -- Initialize Animations
        m_Anim[PlayerDir::Right] = g_RscManager->GetAnimation(Animations::Player_Reload);
    }

    PlayerReloadState::~PlayerReloadState()
    {
    }

    void PlayerReloadState::OnEntry(PlayerData& data)
    {
        PlayerState::OnEntry(data);
    }

    void PlayerReloadState::OnUpdate(PlayerData& data)
    {
        PlayerState::OnUpdate(data);
    }

    void PlayerReloadState::OnExit(PlayerData& data)
    {
        data.m_BulletsInMag = MAG_CAPACITY;
    }
}
