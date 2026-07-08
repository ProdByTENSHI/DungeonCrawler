#pragma once

#include "Enemy.hpp"
#include "EnemyFSM.hpp"
#include "engine/entities/Entity.hpp"

namespace tenshi
{
    class Drone : public Enemy
    {
    public:
        explicit Drone(u32 id, const std::string& name = "Drone");
        ~Drone() override;

        void Die() override;
        void Hit(u32 damage) override;
        void Update() override;
        RenderCommand CreateRenderCommand() override;

    private:
        EnemyStates ResolveState() override;
    };
}
