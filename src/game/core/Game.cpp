#include "game/core/Game.hpp"
#include "engine/globals/Constants.hpp"
#include "engine/globals/Globals.hpp"

#include "game/player/Player.hpp"
#include "raylib.h"
#include "engine/input/InputManager.hpp"

namespace tenshi
{
    Player* player = nullptr;

    Game::Game()
    {
        InitWindow(g_WindowWidth, g_WindowHeight, "Dungeon Crawler");

        // -- INIT GLOBAL SYSTEMS
        g_RscManager = std::make_unique<RscManager>();
        g_RscManager->LoadAssets();

        g_EntityManager = std::make_unique<EntityManager>();
        g_MasterRenderer = std::make_unique<MasterRenderer>();
        g_InputManager = std::make_unique<InputManager>();
        g_MainCam = std::make_unique<AuroraCam>();
        g_WorldManager = std::make_unique<WorldManager>();

        g_WorldManager->LoadWorldSection("Test_Section");
        player = g_EntityManager->CreateEntity<Player>();
        g_MainCam->SetFollowTarget(&player->m_Position);

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

        g_MasterRenderer->Render();
    }
}
