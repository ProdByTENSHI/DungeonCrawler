#pragma once

#include "UIBase.hpp"

#include <vector>
#include <map>

#include "spdlog/spdlog.h"

namespace tenshi
{
    class UIManager
    {
    public:
        UIManager();
        ~UIManager() {}

        template <typename T, typename... Args>
        requires std::is_base_of_v<UIBase, T>
        T* CreateUIComponent(Args &&... args)
        {
            u16 _id;
            if (m_FreeIdsBuffer.empty())
            {
                _id = m_IdCounter;
                ++m_IdCounter;
            } else
            {
                _id = m_FreeIdsBuffer.back();
                m_FreeIdsBuffer.pop_back();
            }

            T* component = new T(_id, args...);
            if (!component)
            {
                spdlog::error("Could not create UI Component");
                delete component;
                return nullptr;
            }

            m_ComponentCreationBuffer.push_back(component);

            return component;
        }

        void DeleteUIComponent(u16 id);

        void Update();
        void Render();
        void AfterUIFinished();

    private:
        void RecursiveDraw(UIBase& component) const;

    private:
        std::vector<UIBase*> m_Components;
        std::vector<u16> m_FreeIdsBuffer;
        std::map<u16, size_t> m_ComponentsLUT;

        std::vector<UIBase*> m_ComponentCreationBuffer;
        std::vector<UIBase*> m_ComponentDeletionBuffer;

        u32 m_IdCounter = 0;

    };
}
