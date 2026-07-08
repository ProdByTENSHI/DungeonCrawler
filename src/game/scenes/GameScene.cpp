#include "game/scenes/GameScene.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    GameScene::GameScene(u16 id, const std::string& name)
        : Scene(id, name)
    {
    }

    GameScene::~GameScene()
    {
    }

    bool GameScene::Load()
    {
        g_WorldManager->LoadWorldSection("Test_Section");

        return true;
    }

    void GameScene::Enter()
    {
        m_Player = g_EntityManager->CreateEntity<Player>();
        m_Player->m_PlayerData.m_Position = {128.0f, 128.0f};
        g_MainCam->SetFollowTarget(&m_Player->m_Position, {0.0f, -PlayerConstants::SIZE.y});

        Drone* drone = g_EntityManager->CreateEntity<Drone>();
        drone->m_Data.m_Position = {256.0f, 256.0f};

        m_Enemies.push_back(drone);

        // -- Dbg
        EventHandler<KeyEvent> _debugToggle([](KeyEvent e)
        {
            if (e.m_KeyCode != KEY_P)
                return;

            g_IsInDebugMode = !g_IsInDebugMode;
        });
        OnKeyPressedEvent.Subscribe(_debugToggle);
    }

    void GameScene::Update()
    {
        g_InputManager->UpdateInputEvents();

        g_MainCam->Update();

        g_WorldManager->Update();
        g_EntityManager->UpdateEntities();
    }

    void GameScene::Render()
    {
        g_WorldManager->Render();
        g_EntityManager->RenderEntities();
        g_EntityManager->AfterEntitiesFinished();
    }

    void GameScene::Exit()
    {
    }
}
