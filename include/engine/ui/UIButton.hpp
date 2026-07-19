#pragma once
#include "UIBase.hpp"
#include "engine/graphics/SpriteSheet.hpp"
#include "engine/input/InputEvents.hpp"
#include "engine/tenshiUtil/eventsystem/EventSystem.h"

namespace tenshi
{
    class UIButton : public UIBase
    {
    public:
        UIButton(u16 id, UIComponentType type = UIComponentType::Button);
        ~UIButton() override;

        RenderCommand Render() override;

    public:
        Event<> OnClicked;

    private:
        EventHandler<MouseEvent> OnClickedHandler;
    };
}
