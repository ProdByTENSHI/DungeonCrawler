#pragma once

#include "engine/entities/Entity.hpp"
#include "engine/graphics/Animation.hpp"

namespace tenshi
{
    struct Projectile : public Entity
    {
        Projectile(u32 id, const std::string& name = "Projectile");
        ~Projectile() override;

        void Update() override;

        RenderCommand CreateRenderCommand() override;

        u32 m_Damage = 5;
        f32 m_Rotation = 0.0f;

        Vector2 m_Velocity = Vector2(0.0f, 0.0f);
        Vector2 m_Size = Vector2(32.0f, 32.0f);

        Animation* m_Anim = nullptr;
    };
}
