#pragma once

#include "engine/scenes/Scene.hpp"

#include "game/player/Player.hpp"
#include "game/enemies/Drone.hpp"

namespace tenshi
{
    class GameScene : public Scene
    {
    public:
        GameScene(u16 id, const std::string& name);
        ~GameScene();

        bool Load() override;
        void Enter() override;
        void Update() override;
        void Render() override;
        void Exit() override;

    private:
        Player* m_Player = nullptr;

        std::vector<Enemy*> m_Enemies;
    };
}