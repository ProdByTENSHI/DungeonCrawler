#pragma once

#include "engine/tenshiUtil/Types.hpp"
#include "engine/render/RenderCommand.hpp"

#include <raylib.h>
#include <string>

namespace tenshi
{
    enum class EntityType : u8
    {
        Player = 0,
        Enemy = 1,
        NPC = 2,
        Projectile = 3
    };

    // Base Class for all Entities
    class Entity {
    public:
        explicit Entity(u32 id, const std::string &name = "",
            EntityType type = EntityType::Enemy)
        : m_Id(id), m_Name(name), m_Type(type) {
        }

        virtual ~Entity() {
        }

        virtual void Update() = 0;

        virtual RenderCommand CreateRenderCommand() = 0;
        virtual Rectangle GetBoundingBox() const = 0;

    public:
        const u32 m_Id;
        const std::string m_Name;
        const EntityType m_Type;

        Vector2 m_Position = {0.0f, 0.0f};

        bool m_IsCollider = true;
        bool m_HasLimitedLifeTime = false;
        f32 m_TotalLifeTime = -1;

        // Only gets updated if the Entity has a limited Life Time
        f32 m_CurrentLifeTime = 0;

    private:
        static u32 s_IdCounter;
    };
}