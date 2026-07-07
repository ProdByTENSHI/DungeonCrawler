#pragma once

#include "engine/entities/Entity.hpp"
#include "engine/graphics/Animation.hpp"

namespace tenshi
{
    struct Projectile : public Entity
    {
        Projectile(u32 id, const std::string& name = "Projectile",
            u32 shooterId = 0);
        ~Projectile() override;

        void Update() override;

        RenderCommand CreateRenderCommand() override;
        Rectangle GetBoundingBox() const override;

        u32 m_Damage = 5;
        f32 m_Speed = 250.0f;
        f32 m_Rotation = 0.0f;

        Vector2 m_Velocity = Vector2(0.0f, 0.0f);
        Vector2 m_Size = Vector2(32.0f, 32.0f);

        Animation* m_Anim = nullptr;

    protected:
        std::vector<Entity*> m_HitEntities;

        // Entity ID of the Shooter
        u32 m_ShooterId = 0;

    private:
        void ResolveCollision();

    private:
        bool m_HasHit = false;
    };
}
