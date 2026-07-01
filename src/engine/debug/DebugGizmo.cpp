#include "engine/debug/DebugGizmo.hpp"
#include "engine/globals/Globals.hpp"

namespace tenshi
{
    void DrawRectGizmo(Rectangle bounds, Color color)
    {
        DebugGizmo _gizmo;
        _gizmo.m_Color = color;
        _gizmo.m_BoundingBox = bounds;
        _gizmo.m_Type = GizmoType::Rectangle;

        g_MasterRenderer->PushDebugGizmo(_gizmo);
    }
}
