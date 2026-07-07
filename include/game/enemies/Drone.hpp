#pragma once

#include "Enemy.hpp"
#include "EnemyFSM.hpp"
#include "engine/entities/Entity.hpp"

namespace tenshi
{
    class Drone : public Enemy
    {
    public:
        Drone(u32 id, const std::string& name = "Drone");
        ~Drone();

        void Update() override;
        RenderCommand CreateRenderCommand() override;

    private:
    };
}
