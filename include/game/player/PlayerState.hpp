#pragma once

#include <map>

#include "engine/tenshiUtil/Types.hpp"
#include "engine/graphics/Animation.hpp"
#include "game/player/PlayerData.hpp"

namespace tenshi
{
    enum class PlayerStates : u8
    {
        Idle,
        Walk,
        Run,
        LAST
    };

    struct PlayerState
    {
        PlayerState(PlayerStates state)
            : m_State(state) {}
        virtual ~PlayerState() {}

        virtual void OnEntry(PlayerData& data) = 0;
        virtual void OnUpdate(PlayerData& data)
        {
            m_Anim[data.m_Direction]->Update();
        }
        virtual void OnExit(PlayerData& data) = 0;

        const PlayerStates m_State;

        // Same order as PlayerDir Enum
        std::map<PlayerDir, Animation*> m_Anim;
    };
}
