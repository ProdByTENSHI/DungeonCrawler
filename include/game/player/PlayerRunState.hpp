#pragma once

#include "game/player/PlayerState.hpp"

namespace tenshi
{
    struct PlayerRunState : public PlayerState
    {
        PlayerRunState();
        ~PlayerRunState();

        void OnEntry(PlayerData& data) override;
        void OnUpdate(PlayerData& data) override;
        void OnExit(PlayerData& data) override;
    };
}