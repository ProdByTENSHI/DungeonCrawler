#pragma once

#include "engine/entities/EntityManager.hpp"
#include "engine/memory/RscManager.hpp"
#include "engine/render/MasterRenderer.hpp"
#include "engine/world/WorldManager.hpp"
#include "engine/camera/AuroraCam.hpp"

#include <memory>

#include "engine/input/InputManager.hpp"

namespace tenshi
{
    inline i32 g_WindowWidth = 1280;
    inline i32 g_WindowHeight = 720;

    inline std::unique_ptr<MasterRenderer> g_MasterRenderer;
    inline std::unique_ptr<RscManager> g_RscManager;
    inline std::unique_ptr<EntityManager> g_EntityManager;
    inline std::unique_ptr<WorldManager> g_WorldManager;
    inline std::unique_ptr<InputManager> g_InputManager;
    inline std::unique_ptr<AuroraCam> g_MainCam;

    inline bool g_IsInDebugMode = true;
}
