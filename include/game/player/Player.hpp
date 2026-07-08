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
#include "game/player/PlayerConstants.hpp"

namespace tenshi
{
    class Player : public Entity
    {
    public:
        Player(u32 id, const std::string& name = "Player",
            EntityType type = EntityType::Player);
        ~Player() override;

        void Hit(u32 damage);
        void Die();

        void Update() override;
        RenderCommand CreateRenderCommand() override;

        Tile* GetTilePlayerIsOn() const;

        Rectangle GetBoundingBox() const override;

    public:
        PlayerData m_PlayerData;

    private:
        // Returns the State to Transition to
        PlayerStates ResolveState();

        void ResolveCollision();

    private:
        EventHandler<> ShootHandler;
        EventHandler<> ReloadHandler;

        PlayerFSM* m_PlayerFSM = nullptr;

        PlayerInput* m_Input = nullptr;
        std::vector<PlayerInputController*> m_InputControllers;
    };
}
