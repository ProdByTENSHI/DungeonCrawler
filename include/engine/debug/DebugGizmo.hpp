#pragma once

#include "engine/tenshiUtil/Types.hpp"

#include "raylib.h"

namespace tenshi
{
    enum class GizmoType : u8
    {
        Rectangle,
        Circle
    };

    struct DebugGizmo
    {
        GizmoType m_Type = GizmoType::Rectangle;
        Color m_Color = WHITE;

        // For Circle the Width = Radius
        Rectangle m_BoundingBox;
    };

    void DrawRectGizmo(Rectangle bounds, Color color);
}
