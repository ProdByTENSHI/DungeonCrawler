#include "game/scenes/GameScene.hpp"

#include "engine/globals/Globals.hpp"
#include "engine/ui/UIButton.hpp"
#include "engine/ui/UIPanel.hpp"

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

        for (i32 i = 0; i < 5; i++)
        {
            Drone* drone = g_EntityManager->CreateEntity<Drone>();
            drone->m_Data.m_Position = {32 + 32.0f * i, 32 + 32.0f * i};
            m_Enemies.push_back(drone);
        }

        UIPanel* testPanelLeft = g_UIManager->CreateUIComponent<UIPanel>();
        testPanelLeft->SetRelativeOffset({0.0f, 0.0f});
        testPanelLeft->SetRelativeSize({1.0f, 0.1f});
        testPanelLeft->SetColor(BLACK);

        UIButton* testButton = g_UIManager->CreateUIComponent<UIButton>();
        testButton->SetParent(testPanelLeft);
        testButton->SetRelativeOffset({0.25f, 0.25f});
        testButton->SetRelativeSize({0.5f, 0.5f});
        testButton->SetColor(WHITE);

        EventHandler<> btnClick = EventHandler<>([this]()
        {
            spdlog::info("Clicked Button!");
        });
        testButton->OnClicked.Subscribe(btnClick);

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
        g_UIManager->Update();
    }

    void GameScene::Render()
    {
        g_WorldManager->Render();

        g_EntityManager->RenderEntities();
        g_EntityManager->AfterEntitiesFinished();

        g_UIManager->Render();
        g_UIManager->AfterUIFinished();
    }

    void GameScene::Exit()
    {
    }
}
