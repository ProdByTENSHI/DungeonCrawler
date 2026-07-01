#pragma once

#include "engine/entities/Entity.hpp"
#include "game/player/PlayerState.hpp"
#include "game/player/PlayerData.hpp"

#include <unordered_map>

#include "raylib.h"

namespace tenshi
{
    class Player : public Entity
    {
    public:
        Player(u32 id, const std::string name = "Player");
        ~Player();

        void Update() override;
        RenderCommand CreateRenderCommand() override;

        void SetState(PlayerStates state);

    private:
        void HandleInput();

    public:
        PlayerStates m_CurrentStateType = PlayerStates::Idle;

        PlayerData m_PlayerData;

    private:
        const f32 WALK_SPEED = 10.0f;
        const f32 RUN_SPEED = 25.0f;

        Vector2 m_Size = {59.0f, 49.0f};

        std::unordered_map<PlayerStates, PlayerState*> m_StatesTable;

        PlayerState* m_CurrentState = nullptr;
    };
}
