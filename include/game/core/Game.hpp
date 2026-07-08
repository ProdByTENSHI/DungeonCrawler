#pragma once
#include "engine/tenshiUtil/Types.hpp"

namespace tenshi
{
    class Game
    {
    public:
        Game();
        ~Game();

        void Update();
        void Render();

    private:
        void ResizeWindow(i32 width, i32 height);

    private:
        bool m_IsRunning = false;

        i32 m_MonitorWidth = 0;
        i32 m_MonitorHeight = 0;
    };
}
