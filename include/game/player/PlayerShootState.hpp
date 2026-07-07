#pragma once

#include "game/player/PlayerState.hpp"
#include "game/projectiles/Projectile.hpp"

namespace tenshi
{
    struct PlayerShootState : public PlayerState
    {
        PlayerShootState();
        ~PlayerShootState();

        void OnEntry(PlayerData& data) override;
        void OnUpdate(PlayerData& data) override;
        void OnExit(PlayerData& data) override;

        std::vector<Projectile*> m_Projectiles;
    };
}
