#include "engine/scenes/SceneManager.hpp"

namespace tenshi
{
    SceneManager::SceneManager()
    {
    }

    SceneManager::~SceneManager()
    {
    }

    void SceneManager::LoadScene(u16 scene)
    {
        if (m_Scenes[scene] == nullptr)
        {
            spdlog::info("Could not load Scene {}", scene);
            return;
        }

        bool _loadStatus = m_Scenes[scene]->Load();
        if (!_loadStatus)
        {
            throw std::runtime_error("Something went wrong during Scene Loading");
        }

        if (m_CurrentScene)
            UnloadScene();

        m_CurrentScene = m_Scenes[scene];
        m_CurrentScene->Enter();
    }

    void SceneManager::UnloadScene()
    {
        m_CurrentScene->Exit();
    }

    void SceneManager::Update()
    {
        m_CurrentScene->Update();
    }

    void SceneManager::Render()
    {
        m_CurrentScene->Render();
    }

    u16 SceneManager::GetSceneIdByName(const std::string& name) const
    {
        for (auto& scene : m_Scenes)
        {
            if (scene.second->m_Name == name)
                return scene.first;
        }

        spdlog::info("Could not find Scene {}", name);
        return 0xFFFF;
    }
}
