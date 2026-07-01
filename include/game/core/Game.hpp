#pragma once

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
        bool m_IsRunning = false;

    };
}