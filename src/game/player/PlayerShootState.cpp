#include "game/player/PlayerShootState.hpp"

#include "raymath.h"
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
        p->m_Position.x = data.m_Position.x + (PlayerConstants::SIZE.x * 0.5f);
        p->m_Position.y = data.m_Position.y + (PlayerConstants::SIZE.y * 0.5f);

        if (data.m_LastFacingDirection == PlayerDir::Right)
        {
            p->m_Position.x += PlayerConstants::MUZZLE_OFFSET.x;
        } else if (data.m_LastFacingDirection == PlayerDir::Left)
        {
            p->m_Position.x -= PlayerConstants::MUZZLE_OFFSET.x;
        }

        p->m_Position.y += PlayerConstants::MUZZLE_OFFSET.y;

        // -- Calculate Projectile Direction and Rotation
        Vector2 _mouse = g_InputManager->GetMouseWorldPosition();

        Vector2 _dir = Vector2Subtract(_mouse,
            p->m_Position);
        _dir = Vector2Normalize(_dir);

        p->m_Velocity.x = _dir.x * p->m_Speed;
        p->m_Velocity.y = _dir.y * p->m_Speed;

        p->m_Rotation = atan2(_dir.y, _dir.x) * RAD2DEG;
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
