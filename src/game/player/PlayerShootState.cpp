#include "game/player/PlayerShootState.hpp"

#include "engine/globals/Globals.hpp"
#include "game/player/PlayerConstants.hpp"

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

        Projectile* p = g_EntityManager->CreateEntity<Projectile>("Player_Projectile");
        m_Projectiles.push_back(p);

        p->m_Anim = g_RscManager->GetAnimation(Animations::Projectile_Laser);

        if (data.m_LastFacingDirection == PlayerDir::Right)
        {
            p->m_Position.x = data.m_Position.x + player_constants::SIZE.x * 0.5f;
        } else if (data.m_LastFacingDirection == PlayerDir::Left)
        {
            p->m_Position.x = data.m_Position.x - player_constants::SIZE.x * 0.5f;
        }

        p->m_Position.y = data.m_Position.y + (player_constants::SIZE.y * 0.25f);

        // -- Calculate Projectile Direction and Rotation
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
