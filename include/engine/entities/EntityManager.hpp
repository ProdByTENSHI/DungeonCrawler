#pragma once

#include "engine/entities/Entity.hpp"

#include <vector>
#include <unordered_map>
#include <type_traits>

#include "game/projectiles/Projectile.hpp"

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
            T *entity;
            if (m_FreeEntityIds.empty())
            {
                entity = new T(s_IdCounter, args...);
                ++s_IdCounter;
            } else
            {
                entity = new T(m_FreeEntityIds.back(), args...);
                m_FreeEntityIds.pop_back();
            }
            m_EntityCreationBuffer.push_back(entity);

            return entity;
        }

        // Deffer Entity Deletion to the end of Update to prevent Iteration Bugs
        void DestroyEntity(Entity& entity);
        void DestroyEntity(u32 id);
#pragma endregion Entity Lifetime

        void UpdateEntities();

        void AfterEntitiesFinished();

        void RenderEntities();

#pragma region Entity Util
        Entity *GetEntityById(u32 entityId);

        bool CheckCollision(Rectangle bbox, std::vector<Entity*>* colliders);

        bool IsValidEntity(u32 entityId);
#pragma endregion Entity Util

    private:
        inline static u32 s_IdCounter = 0;
        std::vector<Entity*> m_EntityCreationBuffer;
        std::vector<Entity *> m_Entities;
        std::unordered_map<u32, size_t> m_EntityIdLUT;

        // When deleting an Entity we defer it to the End of the Frame
        std::vector<Entity *> m_EntityDeletionBuffer;

        // Buffer that holds Entity IDs that have been freed
        std::vector<u32> m_FreeEntityIds;
    };
}
