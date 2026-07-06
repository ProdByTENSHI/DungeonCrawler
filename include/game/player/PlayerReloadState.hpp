#pragma once

#include "game/player/PlayerState.hpp"

namespace tenshi
{
    struct PlayerReloadState : public PlayerState
    {
        PlayerReloadState();
        ~PlayerReloadState();

        void OnEntry(PlayerData& data) override;
        void OnUpdate(PlayerData& data) override;
        void OnExit(PlayerData& data) override;
    };
}