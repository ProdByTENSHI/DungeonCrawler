#pragma once

#include "engine/tenshiUtil/eventsystem/EventSystem.h"

namespace tenshi
{
    inline Event<> OnUpdateEvent;
    inline Event<> OnRenderEvent;
    inline Event<> OnUiRenderEvent;
}