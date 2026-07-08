#pragma once
#include <map>

#include "GenericEnemyData.hpp"
#include "engine/graphics/Animation.hpp"
#include "engine/tenshiUtil/Types.hpp"

namespace tenshi
{
    enum class EnemyStates : u8
    {
        Idle = 0,
        Run = 2,
        Shoot = 3,
        Activate = 4,
        Deactivate = 5,
        Hit = 6,
        Die = 7
    };

    class EnemyState
    {
    public:
        explicit EnemyState(const EnemyStates state)
            : m_State(state) {}
        virtual ~EnemyState() {}

        virtual void OnEntry(GenericEnemyData& data) { m_TimeSinceStateEntry = 0.0f;}
        virtual void OnUpdate(GenericEnemyData& data) {m_Anim->Update(); m_TimeSinceStateEntry += GetFrameTime();}
        virtual void OnExit(GenericEnemyData& data) = 0;

        bool HasAnimFinished(GenericEnemyData& data)
        {
            return m_TimeSinceStateEntry >= m_Anim->m_Interval * m_Anim->m_Frames.size();
        }

    public:
        const EnemyStates m_State;

        f32 m_TimeSinceStateEntry = 0.0f;

        Animation* m_Anim = nullptr;

    };
}
