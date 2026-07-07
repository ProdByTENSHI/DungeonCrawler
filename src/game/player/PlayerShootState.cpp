#include "game/player/PlayerShootState.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    PlayerShootState::PlayerShootState()
        :  PlayerState(PlayerStates::Shoot)
    {
        // -- Initialize Animations
        m_Anim[PlayerDir::Right] = g_RscManager->GetAnimation(Animations::Player_Shoot);
    }

    PlayerShootState::~PlayerShootState()
    {
    }

    void PlayerShootState::OnEntry(PlayerData& data)
    {
        PlayerState::OnEntry(data);
        --data.m_BulletsInMag;
        g_MainCam->ShakeCamera(5.0f, 48);
    }

    void PlayerShootState::OnUpdate(PlayerData& data)
    {
        PlayerState::OnUpdate(data);
    }

    void PlayerShootState::OnExit(PlayerData& data)
    {
        data.m_TimeSinceAttack = 0.0f;
    }
}
