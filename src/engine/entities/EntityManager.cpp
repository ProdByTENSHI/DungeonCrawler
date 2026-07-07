#include "engine/entities/EntityManager.hpp"
#include "engine/globals/Globals.hpp"

#include <spdlog/spdlog.h>
#include <algorithm>

namespace tenshi
{
    EntityManager::EntityManager() {
        m_EntityLayerId = g_MasterRenderer->GetRenderLayerIdByName("Entities");
    }

    EntityManager::~EntityManager() {
        m_EntityIdLUT.clear();
        for (i32 i = 0; i < m_Entities.size(); i++) {
            delete m_Entities[i];
            m_Entities.erase(m_Entities.begin() + i);
        }
    }

    void EntityManager::DestroyEntity(Entity& entity) {
        if (!IsValidEntity(entity.m_Id)) {
            return;
        }

        m_EntityDeletionBuffer.push_back(&entity);
    }

    void EntityManager::UpdateEntities() {
        for (auto& entity : m_Entities)
        {
            entity->Update();

            if (entity->m_HasLimitedLifeTime)
            {
                if (entity->m_CurrentLifeTime >= entity->m_TotalLifeTime)
                {
                    DestroyEntity(*entity);
                    continue;
                }

                entity->m_CurrentLifeTime += GetFrameTime();
            }
        }
    }

    void EntityManager::RenderEntities() {
        for (auto& entity : m_Entities)
        {
            g_MasterRenderer->PushRenderCommand(m_EntityLayerId,
                entity->CreateRenderCommand());
        }
    }

    void EntityManager::AfterEntitiesFinished() {
        // -- Deferred Deletion
        for (auto& entity : m_EntityDeletionBuffer)
        {
            auto it = m_EntityIdLUT.find(entity->m_Id);
            if (it == m_EntityIdLUT.end())
                continue;

            size_t _index = it->second;
            size_t _last = m_Entities.size() - 1;

            if (_index != _last)
            {
                std::swap(m_Entities[_index], m_Entities[_last]);
                m_EntityIdLUT[m_Entities[_index]->m_Id] = _index;
            }


            m_EntityIdLUT.erase(entity->m_Id);
            m_FreeEntityIds.push_back(entity->m_Id);

            delete m_Entities.back();

            m_Entities.pop_back();
        }

        m_EntityDeletionBuffer.clear();

        // -- Deferred Creation
        for (i32 i = 0; i < m_EntityCreationBuffer.size(); i++)
        {
            m_Entities.push_back(m_EntityCreationBuffer[i]);
            m_EntityIdLUT[m_EntityCreationBuffer[i]->m_Id] = m_Entities.size() - 1;
        }

        m_EntityCreationBuffer.clear();
    }

    Entity *EntityManager::GetEntityById(u32 entityId) {
        if (!IsValidEntity(entityId)) {
            return nullptr;
        }

        return m_Entities[m_EntityIdLUT[entityId]];
    }

    bool EntityManager::CheckCollision(Rectangle bbox, std::vector<Entity*>* colliders)
    {
        bool _hasCollided = false;
        for (auto& entity : m_Entities)
        {
            if (CheckCollisionRecs(bbox, entity->GetBoundingBox()))
            {
                if (colliders != nullptr)
                    colliders->push_back(entity);

                _hasCollided = true;
            }
        }

        return _hasCollided;
    }

    bool EntityManager::IsValidEntity(u32 entityId) {
        if (m_Entities[m_EntityIdLUT[entityId]] == nullptr)
        {
            spdlog::info("Entity {} is not existing", entityId);
            return false;
        }

        // Check if Entity is planned for deletion
        if (std::find(m_EntityDeletionBuffer.begin(), m_EntityDeletionBuffer.end(),
            m_Entities[m_EntityIdLUT[entityId]]) != m_EntityDeletionBuffer.end()) {
            spdlog::error("Entity {} was destroyed and is not valid", entityId);
            return false;
        }

        return true;
    }
}
