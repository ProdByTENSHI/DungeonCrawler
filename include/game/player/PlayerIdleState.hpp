#pragma once

#include "game/player/PlayerState.hpp"

namespace tenshi
{
    struct PlayerIdleState : public PlayerState
    {
        PlayerIdleState();
        ~PlayerIdleState();

        void OnEntry(PlayerData& data) override;
        void OnUpdate(PlayerData& data) override;
        void OnExit(PlayerData& data) override;
    };
}