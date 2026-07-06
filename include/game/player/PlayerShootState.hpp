#pragma once

#include "game/player/PlayerState.hpp"

namespace tenshi
{
    struct PlayerShootState : public PlayerState
    {
        PlayerShootState();
        ~PlayerShootState();

        void OnEntry(PlayerData& data) override;
        void OnUpdate(PlayerData& data) override;
        void OnExit(PlayerData& data) override;
    };
}