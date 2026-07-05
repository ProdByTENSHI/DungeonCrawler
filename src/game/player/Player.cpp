#include "game/player/Player.hpp"

#include "engine/globals/Globals.hpp"
#include "game/player/PlayerIdleState.hpp"

#include <raylib.h>

#include "raymath.h"
#include "game/player/PlayerRunState.hpp"

namespace tenshi
{
    Player::Player(u32 id, const std::string name)
        : Entity(id, name), m_Input()
    {
        // -- Initialize States Table
        m_StatesTable[PlayerStates::Idle] = new PlayerIdleState();
        m_StatesTable[PlayerStates::Run] = new PlayerRunState();

        SetState(PlayerStates::Idle);

        // -- Input Controllers
        m_Input = new PlayerInput();
        m_InputControllers.push_back(m_Input);
    }

    Player::~Player()
    {
        delete m_CurrentState;
        delete m_Input;
    }

    void Player::Update()
    {
        if (!m_CurrentState)
            return;

        // -- Handle Input
        for (auto& c : m_InputControllers)
        {
            c->HandleData(m_PlayerData);
        }

        if (abs(m_PlayerData.m_Velocity.x) > 0 || abs(m_PlayerData.m_Velocity.y) > 0)
        {
            m_PlayerData.m_IsMoving = true;
            SetState(PlayerStates::Run);
        } else
        {
            m_PlayerData.m_IsMoving = false;
            SetState(PlayerStates::Idle);
        }

        if (m_PlayerData.m_Velocity.x > 0.0f && m_PlayerData.m_Velocity.y > 0.0f)
        {
            f32 _desiredVal = MOVEMENT_SPEED * 0.5f;
            m_PlayerData.m_Velocity.x = _desiredVal;
            m_PlayerData.m_Velocity.y = _desiredVal;
        }

        // Player Facing
        if (m_PlayerData.m_Velocity.x < 0.0f && m_PlayerData.m_LastFacingDirection == PlayerDir::Right)
        {
            m_PlayerData.m_LastFacingDirection = PlayerDir::Left;
        } else if (m_PlayerData.m_Velocity.x > 0.0f && m_PlayerData.m_LastFacingDirection == PlayerDir::Left)
        {
            m_PlayerData.m_LastFacingDirection = PlayerDir::Right;
        }

        m_PlayerData.m_Position.x += m_PlayerData.m_Velocity.x * GetFrameTime();
        m_PlayerData.m_Position.y += m_PlayerData.m_Velocity.y * GetFrameTime();

        ResolveCollision();

        m_Position = m_PlayerData.m_Position;
        m_CurrentState->OnUpdate(m_PlayerData);
    }

    RenderCommand Player::CreateRenderCommand()
    {
        DrawRectGizmo(GetBoundingBox(), RED);
        RenderCommand _cmd = {};

        if (!m_CurrentState)
            return _cmd;

        _cmd = m_CurrentState->m_Anim[PlayerDir::Right]->GetRenderCommand();
        _cmd.m_DstRect = {m_Position.x, m_Position.y,
            m_Size.x * m_PlayerData.m_Scale.x, m_Size.y * m_PlayerData.m_Scale.y};

        // Sprite Flipping based on Left Right Facing Direction
        if (m_PlayerData.m_LastFacingDirection == PlayerDir::Left)
        {
            _cmd.m_SrcRect.width *= -1;
        }

        return _cmd;
    }

    void Player::SetState(PlayerStates state)
    {
        if (m_CurrentState != nullptr)
            m_CurrentState->OnExit(m_PlayerData);

        m_CurrentState = m_StatesTable[state];
        if (!m_CurrentState)
            spdlog::error("Player State {} not in Table", (u8)state);
        m_CurrentState->OnEntry(m_PlayerData);
    }

    Tile* Player::GetTilePlayerIsOn()
    {
        u32 _x = static_cast<u32>((m_PlayerData.m_Position.x + TILE_SIZE * 0.5f) / TILE_SIZE);
        u32 _y = static_cast<u32>((m_PlayerData.m_Position.y + TILE_SIZE * 0.5f) / TILE_SIZE);

        return g_WorldManager->GetTile(Vector2Int(_x,_y));
    }

    Tile* Player::GetTileNextToPlayer(NSWE dir)
    {
        u32 _x = 0;
        u32 _y = 0;

        switch (dir)
        {
        case NSWE::CENTER:
            return GetTilePlayerIsOn();

        case NSWE::NORTH:
            _x = static_cast<u32>(m_PlayerData.m_Position.x / TILE_SIZE);
            _y = static_cast<u32>((m_PlayerData.m_Position.y - TILE_SIZE) / TILE_SIZE);
            return g_WorldManager->GetTile(Vector2Int(_x, _y));

        case NSWE::SOUTH:
            _x = static_cast<u32>(m_PlayerData.m_Position.x / TILE_SIZE);
            _y = static_cast<u32>((m_PlayerData.m_Position.y + TILE_SIZE) / TILE_SIZE);
            return g_WorldManager->GetTile(Vector2Int(_x, _y));

        case NSWE::WEST:
            _x = static_cast<u32>((m_PlayerData.m_Position.x - TILE_SIZE)/ TILE_SIZE);
            _y = static_cast<u32>(m_PlayerData.m_Position.y / TILE_SIZE);
            return g_WorldManager->GetTile(Vector2Int(_x, _y));

        case NSWE::EAST:
            _x = static_cast<u32>((m_PlayerData.m_Position.x + TILE_SIZE) / TILE_SIZE);
            _y = static_cast<u32>(m_PlayerData.m_Position.y / TILE_SIZE);
            return g_WorldManager->GetTile(Vector2Int(_x, _y));

        case NSWE::NORTH_WEST:
            _x = static_cast<u32>((m_PlayerData.m_Position.x - TILE_SIZE) / TILE_SIZE);
            _y = static_cast<u32>((m_PlayerData.m_Position.y - TILE_SIZE) / TILE_SIZE);
            return g_WorldManager->GetTile(Vector2Int(_x, _y));

        case NSWE::NORTH_EAST:
            _x = static_cast<u32>((m_PlayerData.m_Position.x + TILE_SIZE) / TILE_SIZE);
            _y = static_cast<u32>((m_PlayerData.m_Position.y - TILE_SIZE) / TILE_SIZE);
            return g_WorldManager->GetTile(Vector2Int(_x, _y));

        case NSWE::SOUTH_WEST:
            _x = static_cast<u32>((m_PlayerData.m_Position.x - TILE_SIZE) / TILE_SIZE);
            _y = static_cast<u32>((m_PlayerData.m_Position.y + TILE_SIZE) / TILE_SIZE);
            return g_WorldManager->GetTile(Vector2Int(_x, _y));

        case NSWE::SOUTH_EAST:
            _x = static_cast<u32>((m_PlayerData.m_Position.x + TILE_SIZE) / TILE_SIZE);
            _y = static_cast<u32>((m_PlayerData.m_Position.y + TILE_SIZE) / TILE_SIZE);
            return g_WorldManager->GetTile(Vector2Int(_x, _y));
        }

        spdlog::warn("Tile next to Player in Direction {} is unavailable", (u8)dir);
        return nullptr;
    }

    Rectangle Player::GetBoundingBox() const
    {
        Rectangle _rect;
        _rect.x = m_PlayerData.m_Position.x + 8;
        _rect.y = m_PlayerData.m_Position.y + 16;
        _rect.width = m_BoundingBoxSize.x;
        _rect.height = m_BoundingBoxSize.y;

        return _rect;
    }

    void Player::ResolveCollision()
    {
        // -- Wall Collision --
        Rectangle _boundingBox = GetBoundingBox();
        std::vector<Rectangle> _colliders;
        bool _hasCollided = g_WorldManager->CheckCollision(_boundingBox, &_colliders);

        for (i32 i = 0; i < _colliders.size(); i++)
        {
            // Calculate overlap depths
            float overlapX = (_boundingBox.width + _colliders[i].width) / 2 - fabs(_boundingBox.x - _colliders[i].x);
            float overlapY = (_boundingBox.height + _colliders[i].height) / 2 - fabs(_boundingBox.y - _colliders[i].y);

            // Resolve on the axis with the smallest overlap
            if (overlapX < overlapY) {
                // Horizontal collision
                if (_boundingBox.x < _colliders[i].x) _boundingBox.x -= overlapX;
                else _boundingBox.x += overlapX;
                m_PlayerData.m_Position.x -= m_PlayerData.m_Velocity.x * GetFrameTime();
                m_PlayerData.m_Velocity.x = 0;
            } else if (overlapX >= overlapY) {
                // Vertical collision
                if (_boundingBox.y < _colliders[i].y) _boundingBox.y -= overlapY;
                else _boundingBox.y += overlapY;
                m_PlayerData.m_Position.y -= m_PlayerData.m_Velocity.y * GetFrameTime();
                m_PlayerData.m_Velocity.y = 0;
            }
        }
    }
}
