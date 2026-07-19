#include "engine/ui/UIManager.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    UIManager::UIManager()
    {
    }

    void UIManager::DeleteUIComponent(u16 id)
    {
    }

    void UIManager::Update()
    {
        for (auto& c : m_Components)
        {
            c->Update();
        }
    }

    void UIManager::Render()
    {
        std::vector<RenderCommand> _cmdBuffer;
        for (auto& c : m_Components)
        {
            _cmdBuffer.push_back(c->GetRenderCommand());
        }

        g_MasterRenderer->PushRenderCommandBuffer((u8)RenderLayers::UI, _cmdBuffer);
    }

    void UIManager::AfterUIFinished()
    {
        for (auto& c : m_ComponentCreationBuffer)
        {
            m_Components.push_back(c);
            m_ComponentsLUT.insert({c->m_Id, m_Components.size() - 1});
        }

        m_ComponentCreationBuffer.clear();

        for (auto& c : m_ComponentDeletionBuffer)
        {
            auto it = m_ComponentsLUT.find(c->m_Id);
            if (it == m_Components.end())
                continue;

            size_t _index = it->second;
            size_t _last = m_Components.size() - 1;

            if (_index != _last)
            {
                std::swap(m_Components[_index], m_Components[_last]);
                m_ComponentsLUT[m_Components[_index]->m_Id] = _index;
            }

            m_ComponentsLUT.erase(c->m_Id);
            m_FreeIdsBuffer.push_back(c->m_Id);

            delete m_Components.back();

            m_Components.pop_back();
        }
    }
}
