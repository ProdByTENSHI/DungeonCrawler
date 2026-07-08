#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "engine/scenes/Scene.hpp"
#include "spdlog/spdlog.h"

namespace tenshi
{
    class SceneManager
    {
    public:
        SceneManager();
        ~SceneManager();

        template<typename T>
           requires std::is_base_of_v<Scene, T>
       T *CreateScene(const std::string& name)
        {
            static u16 s_IdCounter = 0;
            T* scene = new T(s_IdCounter, name);
            if (!scene)
            {
                spdlog::info("Could not create Scene");
                return nullptr;
            }

            m_Scenes[s_IdCounter] = scene;

            ++s_IdCounter;

            return scene;
        }

        void LoadScene(u16 scene);
        void UnloadScene();

        void Update();
        void Render();

        u16 GetSceneIdByName(const std::string& name) const;

    private:
        std::unordered_map<u16, Scene*> m_Scenes;

        Scene* m_CurrentScene = nullptr;
    };
}
