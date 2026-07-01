#include "game/player/Player.hpp"

#include "engine/globals/Globals.hpp"
#include "game/player/PlayerIdleState.hpp"

#include <raylib.h>

#include "game/player/PlayerRunState.hpp"

namespace tenshi
{
    Player::Player(u32 id, const std::string name)
        : Entity(id, name)
    {
        // -- Initialize States Table
        m_StatesTable[PlayerStates::Idle] = new PlayerIdleState();
        m_StatesTable[PlayerStates::Run] = new PlayerRunState();

        SetState(PlayerStates::Idle);
    }

    Player::~Player()
    {
    }

    void Player::Update()
    {
        if (!m_CurrentState)
            return;

        m_PlayerData.m_Velocity.x = 15.0f;

        if (m_PlayerData.m_Velocity.x > 0 || m_PlayerData.m_Velocity.y > 0)
        {
            m_PlayerData.m_IsMoving = true;
            SetState(PlayerStates::Run);
        } else
        {
            m_PlayerData.m_IsMoving = false;
            SetState(PlayerStates::Idle);
        }

        m_PlayerData.m_Position.x += m_PlayerData.m_Velocity.x * GetFrameTime();
        m_PlayerData.m_Position.y += m_PlayerData.m_Velocity.y * GetFrameTime();

        m_Position = m_PlayerData.m_Position;
        m_CurrentState->OnUpdate(m_PlayerData);
    }

    RenderCommand Player::CreateRenderCommand()
    {
        RenderCommand _cmd = {};

        if (!m_CurrentState)
            return _cmd;

        _cmd = m_CurrentState->m_Anim[PlayerDir::Right]->GetRenderCommand();
        _cmd.m_DstRect = {m_Position.x, m_Position.y,
            m_Size.x * m_PlayerData.m_Scale.x, m_Size.y * m_PlayerData.m_Scale.y};

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
}
