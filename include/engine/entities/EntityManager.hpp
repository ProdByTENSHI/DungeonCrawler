#pragma once

#include "engine/entities/Entity.hpp"

#include <vector>
#include <unordered_map>
#include <type_traits>

namespace tenshi
{
    class EntityManager {
    public:
        EntityManager();

        ~EntityManager();

#pragma region Entity Lifetime
        template<typename T, typename... Args>
            requires std::is_base_of_v<Entity, T>
        T *CreateEntity(Args &&... args) {
            T *entity = new T(s_IdCounter, args...);

            m_Entities.push_back(entity);
            m_EntityIdLUT[m_Entities.size() - 1] = m_Entities.size() - 1;

            return entity;
        }

        // Deffer Entity Deletion to the end of Update to prevent Iteration Bugs
        void DestroyEntity(Entity& entity);
#pragma endregion Entity Lifetime

        void UpdateEntities();

        void AfterEntitiesFinished();

        void RenderEntities();

#pragma region Entity Util
        Entity *GetEntityById(u32 entityId);

        bool IsValidEntity(u32 entityId);
#pragma endregion Entity Util

    private:
        inline static u32 s_IdCounter = 0;
        std::vector<Entity *> m_Entities;
        std::unordered_map<u32, size_t> m_EntityIdLUT;

        // When deleting an Entity we defer it to the End of the Frame
        std::vector<Entity *> m_EntityDeletionBuffer;

        u16 m_EntityLayerId = 0;
    };
}