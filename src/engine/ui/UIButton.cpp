#include "engine/ui/UIButton.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    UIButton::UIButton(u16 id, UIComponentType type)
        : UIBase(id, type)
    {
        OnClickedHandler = EventHandler<MouseEvent>([this](MouseEvent e)
        {
            Rectangle _boundingBox = {m_Position.x, m_Position.y,
                m_AbsoluteSize.x, m_AbsoluteSize.y};
            Vector2 _mousePos = g_InputManager->GetMouseWorldPosition();
            bool _state =
                CheckCollisionPointRec(_mousePos, _boundingBox);
            if (!_state)
                return;

            OnClicked.Dispatch();
        });
        OnMousePressedEvent.Subscribe(OnClickedHandler);
    }

    UIButton::~UIButton()
    {
        OnMousePressedEvent.Unsubscribe(OnClickedHandler);
    }

    RenderCommand UIButton::Render()
    {
        return UIBase::Render();
    }
}
