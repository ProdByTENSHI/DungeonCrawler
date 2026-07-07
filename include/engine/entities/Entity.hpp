#pragma once

#include "engine/tenshiUtil/Types.hpp"
#include "engine/render/RenderCommand.hpp"

#include <raylib.h>
#include <string>

namespace tenshi
{
    // Base Class for all Entities
    class Entity {
    public:
        explicit Entity(u32 id, const std::string &name = "") : m_Id(id), m_Name(name) {
        }

        virtual ~Entity() {
        }

        virtual void Update() = 0;

        virtual RenderCommand CreateRenderCommand() = 0;

    public:
        const u32 m_Id;
        const std::string m_Name;

        Vector2 m_Position = {0.0f, 0.0f};

        bool m_HasLimitedLifeTime = false;
        f32 m_TotalLifeTime = -1;

        // Only gets updated if the Entity has a limited Life Time
        f32 m_CurrentLifeTime = 0;

    private:
        static u32 s_IdCounter;
    };
}