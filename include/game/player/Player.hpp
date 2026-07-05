#pragma once

#include "engine/entities/Entity.hpp"
#include "game/player/PlayerState.hpp"
#include "game/player/PlayerData.hpp"
#include "game/player/PlayerInput.hpp"

#include <unordered_map>
#include <raylib.h>

#include "engine/world/NSWE.hpp"
#include "engine/world/Tile.hpp"

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

        Tile* GetTilePlayerIsOn();
        Tile* GetTileNextToPlayer(NSWE dir);

        Rectangle GetBoundingBox() const;

    public:
        PlayerStates m_CurrentStateType = PlayerStates::Idle;

        PlayerData m_PlayerData;

    private:
        void ResolveCollision();

    private:
        const f32 WALK_SPEED = 10.0f;
        const f32 RUN_SPEED = 25.0f;

        const Vector2 m_Size = {32.0f, 32.0f};
        const Vector2 m_BoundingBoxSize = {16.0f, 16.0f};

        std::unordered_map<PlayerStates, PlayerState*> m_StatesTable;

        PlayerState* m_CurrentState = nullptr;

        PlayerInput* m_Input = nullptr;
        std::vector<PlayerInputController*> m_InputControllers;
    };
}
