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
        Run,
        Shoot,
        Reload,
        LAST
    };

    struct PlayerState
    {
        PlayerState(PlayerStates state)
            : m_State(state) {}
        virtual ~PlayerState() {}

        virtual void OnEntry(PlayerData& data) {m_TimeSinceStateEntry = 0.0f; };
        virtual void OnUpdate(PlayerData& data)
        {
            m_TimeSinceStateEntry += GetFrameTime();
            m_Anim[data.m_Direction]->Update();
        }
        virtual void OnExit(PlayerData& data) = 0;

        bool HasAnimFinished(PlayerData data)
        {
            return m_TimeSinceStateEntry >= m_Anim[data.m_Direction]->m_Interval * m_Anim[data.m_Direction]->m_Frames.size();
        }

        const PlayerStates m_State;

        f32 m_TimeSinceStateEntry = 0.0f;

        // Same order as PlayerDir Enum
        std::map<PlayerDir, Animation*> m_Anim;
    };
}
