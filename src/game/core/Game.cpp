#include "game/core/Game.hpp"
#include "engine/globals/Globals.hpp"

#include "game/player/Player.hpp"
#include "raylib.h"
#include "engine/input/InputManager.hpp"
#include "game/enemies/Drone.hpp"

namespace tenshi
{
    Player* player = nullptr;

    Game::Game()
    {
        InitWindow(g_WindowWidth, g_WindowHeight, "Dungeon Crawler");

        // -- INIT GLOBAL SYSTEMS
        g_RscManager = std::make_unique<RscManager>();
        g_RscManager->LoadAssets();

        g_MasterRenderer = std::make_unique<MasterRenderer>();
        g_WorldManager = std::make_unique<WorldManager>();
        g_WorldManager->LoadWorldSection("Test_Section");

        g_EntityManager = std::make_unique<EntityManager>();
        g_InputManager = std::make_unique<InputManager>();
        g_MainCam = std::make_unique<AuroraCam>();

        Player* player = g_EntityManager->CreateEntity<Player>();
        player->m_PlayerData.m_Position = {128.0f, 128.0f};
        g_MainCam->SetFollowTarget(&player->m_Position, {0.0f, 0.0f});

        Drone* drone = g_EntityManager->CreateEntity<Drone>();
        drone->m_Data.m_Position = {256.0f, 256.0f};

        // -- Dbg
        EventHandler<KeyEvent> _debugToggle([](KeyEvent e)
        {
            if (e.m_KeyCode != KEY_P)
                return;

            g_IsInDebugMode = !g_IsInDebugMode;
        });
        OnKeyPressedEvent.Subscribe(_debugToggle);

        m_IsRunning = true;
    }

    Game::~Game()
    {
    }

    void Game::Update()
    {
        while (m_IsRunning)
        {
            if (WindowShouldClose())
                m_IsRunning = false;

            g_InputManager->UpdateInputEvents();

            g_WorldManager->Update();
            g_EntityManager->UpdateEntities();
            g_MainCam->Update();

            Render();
        }
    }

    void Game::Render()
    {
        g_WorldManager->Render();
        g_EntityManager->RenderEntities();
        g_EntityManager->AfterEntitiesFinished();

        g_MasterRenderer->Render();
    }
}
