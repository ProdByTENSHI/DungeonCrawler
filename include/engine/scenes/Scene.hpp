#pragma once

#include "engine/tenshiUtil/Types.hpp"

namespace tenshi
{
    // Base Class for all Scenes
    class Scene
    {
    public:
        explicit Scene(u16 id, const std::string& name)
        : m_Id(id), m_Name(name) {}
        virtual ~Scene() {}

        virtual bool Load() = 0;
        virtual void Enter() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Exit() = 0;

    public:
        const u16 m_Id;
        const std::string m_Name;

    };
}