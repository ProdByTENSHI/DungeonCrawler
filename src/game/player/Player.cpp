#include "game/player/Player.hpp"

#include "engine/globals/Globals.hpp"


#include <raylib.h>
#include <raymath.h>

#include "engine/globals/GlobalEvents.hpp"

namespace tenshi
{
    Player::Player(u32 id, const std::string& name, EntityType type)
        : Entity(id, name, type), m_Input()
    {
        m_PlayerFSM = new PlayerFSM();
        m_PlayerFSM->SetState(PlayerStates::Idle, m_PlayerData);

        // -- Input Controllers
        m_Input = new PlayerInput();
        m_InputControllers.push_back(m_Input);

        ShootHandler = EventHandler<>([this]()
        {
            m_PlayerData.m_ShouldShoot = true;
        });

        ReloadHandler = EventHandler<>([this]()
        {
            m_PlayerData.m_ShouldReload = true;
        });

        m_Input->OnShootEvent.Subscribe(ShootHandler);
        m_Input->OnReloadEvent.Subscribe(ReloadHandler);
    }

    Player::~Player()
    {
        delete m_Input;
        delete m_PlayerFSM;
    }

    void Player::Hit(u32 damage)
    {
        m_PlayerData.m_Health -= damage;
        if (m_PlayerData.m_Health <= 0)
            Die();
    }

    void Player::Die()
    {
        spdlog::info("Player died!");
    }

    void Player::Update()
    {
        // -- Handle Input
        for (auto& c : m_InputControllers)
        {
            c->HandleData(m_PlayerData);
        }

        // TODO: Shit Fix do this better but works for now
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

        m_PlayerData.m_TimeSinceAttack += GetFrameTime();

        ResolveCollision();

        m_PlayerFSM->Update(m_PlayerData);
        m_PlayerFSM->SetState(ResolveState(), m_PlayerData);

        if (m_PlayerData.m_ShouldReload)
            spdlog::info("Reload");

        m_PlayerData.m_ShouldReload = false;
        m_PlayerData.m_ShouldShoot = false;

        m_Position = m_PlayerData.m_Position;
    }

    RenderCommand Player::CreateRenderCommand()
    {
        DrawRectGizmo(GetBoundingBox(), RED);
        RenderCommand _cmd = {};

        _cmd = m_PlayerFSM->GetCurrentState()->m_Anim[PlayerDir::Right]->GetRenderCommand();
        _cmd.m_DstRect = {m_Position.x, m_Position.y,
            PlayerConstants::SIZE.x * m_PlayerData.m_Scale.x, PlayerConstants::SIZE.y * m_PlayerData.m_Scale.y};

        // Sprite Flipping based on Left Right Facing Direction
        if (m_PlayerData.m_LastFacingDirection == PlayerDir::Left)
        {
            _cmd.m_SrcRect.width *= -1;
        }

        return _cmd;
    }

    // DOESNT WORK!!!!!!??????
    Tile* Player::GetTilePlayerIsOn() const
    {
        i32 _x = static_cast<i32>((m_PlayerData.m_Position.x + TILE_SIZE * 0.5f) / TILE_SIZE);
        i32 _y = static_cast<i32>((m_PlayerData.m_Position.y + TILE_SIZE * 0.5f) / TILE_SIZE);

        return g_WorldManager->GetTile(Vector2Int(_x,_y));
    }

    Rectangle Player::GetBoundingBox() const
    {
        Rectangle _rect;
        _rect.x = m_PlayerData.m_Position.x + PlayerConstants::BOUNDING_BOX_OFFSET.x;
        _rect.y = m_PlayerData.m_Position.y + PlayerConstants::BOUNDING_BOX_OFFSET.y;
        _rect.width = PlayerConstants::BOUNDING_BOX_SIZE.x;
        _rect.height = PlayerConstants::BOUNDING_BOX_SIZE.y;

        return _rect;
    }

    // TODO: Replace with Transitions to reduce redundant conditions
    PlayerStates Player::ResolveState()
    {
        switch (m_PlayerFSM->GetCurrentStateType())
        {
        case PlayerStates::Idle:
            if (abs(m_PlayerData.m_Velocity.x) > 0 || abs(m_PlayerData.m_Velocity.y) > 0)
            {
                return PlayerStates::Run;
            }

            if (m_PlayerData.m_ShouldShoot
                && m_PlayerData.m_TimeSinceAttack >= TIME_BETWEEN_SHOTS
                && m_PlayerData.m_BulletsInMag > 0)
            {
                m_PlayerData.m_ShouldShoot = false;
                return PlayerStates::Shoot;
            }

            if (m_PlayerData.m_ShouldReload && m_PlayerData.m_BulletsInMag < MAG_CAPACITY)
            {
                m_PlayerData.m_ShouldReload = false;
                return PlayerStates::Reload;
            }
            break;

        case PlayerStates::Run:
            if (abs(m_PlayerData.m_Velocity.x) <= 0.01 && abs(m_PlayerData.m_Velocity.y) <= 0.01)
            {
                return PlayerStates::Idle;
            }

            if (m_PlayerData.m_ShouldShoot
                && m_PlayerData.m_TimeSinceAttack >= TIME_BETWEEN_SHOTS
                && m_PlayerData.m_BulletsInMag > 0)
            {
                m_PlayerData.m_ShouldShoot = false;
                return PlayerStates::Shoot;
            }

            if (m_PlayerData.m_ShouldReload && m_PlayerData.m_BulletsInMag < MAG_CAPACITY)
            {
                m_PlayerData.m_ShouldReload = false;
                return PlayerStates::Reload;
            }
            break;

        case PlayerStates::Shoot:
            if (m_PlayerFSM->GetCurrentState()->HasAnimFinished(m_PlayerData))
            {
                if (abs(m_PlayerData.m_Velocity.x) > 0 || abs(m_PlayerData.m_Velocity.y) > 0)
                {
                    return PlayerStates::Run;
                }

                if (abs(m_PlayerData.m_Velocity.x) <= 0.01 && abs(m_PlayerData.m_Velocity.y) <= 0.01)
                {
                    return PlayerStates::Idle;
                }
            }

            return m_PlayerFSM->GetCurrentStateType();

            break;

        case PlayerStates::Reload:
            if (m_PlayerFSM->GetCurrentState()->HasAnimFinished(m_PlayerData))
            {
                if (abs(m_PlayerData.m_Velocity.x) > 0 || abs(m_PlayerData.m_Velocity.y) > 0)
                {
                    return PlayerStates::Run;
                }

                if (abs(m_PlayerData.m_Velocity.x) <= 0.01 && abs(m_PlayerData.m_Velocity.y) <= 0.01)
                {
                    return PlayerStates::Idle;
                }
            }
            break;

        default:
            break;
        }

        return m_PlayerFSM->GetCurrentStateType();
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
