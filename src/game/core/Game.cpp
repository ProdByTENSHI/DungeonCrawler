#include "game/core/Game.hpp"
#include "engine/globals/Globals.hpp"

#include "game/player/Player.hpp"
#include "raylib.h"
#include "engine/input/InputManager.hpp"
#include "game/enemies/Drone.hpp"
#include "game/scenes/GameScene.hpp"

namespace tenshi
{
    Player* player = nullptr;

    Game::Game()
    {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(g_WindowWidth, g_WindowHeight, "Dungeon Crawler");
        SetWindowMonitor(0);

        i32 _mon = GetCurrentMonitor();
        m_MonitorWidth = GetMonitorWidth(_mon);
        m_MonitorHeight = GetMonitorHeight(_mon);

        // -- INIT GLOBAL SYSTEMS
        g_RscManager = std::make_unique<RscManager>();
        g_RscManager->LoadAssets();

        g_MasterRenderer = std::make_unique<MasterRenderer>();
        g_SceneManager = std::make_unique<SceneManager>();
        g_WorldManager = std::make_unique<WorldManager>();
        g_MainCam = std::make_unique<AuroraCam>();
        g_EntityManager = std::make_unique<EntityManager>();
        g_InputManager = std::make_unique<InputManager>();
        g_UIManager = std::make_unique<UIManager>();

        g_SceneManager->LoadScene(g_SceneManager->CreateScene<GameScene>("Game Scene")->m_Id);

        EventHandler<KeyEvent> _globalKeyEvents([this](KeyEvent e)
        {
            switch (e.m_KeyCode)
            {
            case KEY_F11:
                {
                    ToggleFullscreen();
                    ResizeWindow(m_MonitorWidth, m_MonitorHeight);
                    break;
                }

            default:
                break;
            }
        });
        OnKeyPressedEvent.Subscribe(_globalKeyEvents);

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

            g_SceneManager->Update();

            Render();
        }
    }

    void Game::Render()
    {
        g_SceneManager->Render();

        g_MasterRenderer->Render();
    }

    void Game::ResizeWindow(i32 width, i32 height)
    {
        spdlog::info("{} {}", width, height);
        g_WindowWidth = width;
        g_WindowHeight = height;
    }
}
