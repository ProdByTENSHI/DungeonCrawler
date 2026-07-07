#pragma once

#include "engine/entities/Entity.hpp"
#include "game/player/PlayerState.hpp"
#include "game/player/PlayerData.hpp"
#include "game/player/PlayerInput.hpp"

#include <unordered_map>
#include <raylib.h>

#include "PlayerFSM.hpp"
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

        Tile* GetTilePlayerIsOn();
        Tile* GetTileNextToPlayer(NSWE dir);

        Rectangle GetBoundingBox() const;

    public:
        PlayerData m_PlayerData;

    private:
        // Returns the State to Transition to
        PlayerStates ResolveState();

        void ResolveCollision();

    private:
        const f32 WALK_SPEED = 10.0f;
        const f32 RUN_SPEED = 25.0f;

        const Vector2 m_Size = {32.0f, 32.0f};
        const Vector2 m_BoundingBoxSize = {10.0f, 16.0f};
        const Vector2 m_BoundingBoxOffset = {12.0f, 16.0f};

        EventHandler<> ShootHandler;
        EventHandler<> ReloadHandler;

        PlayerFSM* m_PlayerFSM = nullptr;

        PlayerInput* m_Input = nullptr;
        std::vector<PlayerInputController*> m_InputControllers;
    };
}
