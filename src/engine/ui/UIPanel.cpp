#include "engine/ui/UIPanel.hpp"

namespace tenshi
{
    UIPanel::UIPanel(u16 id, UIComponentType type)
        : UIBase(id, type)
    {
    }

    UIPanel::~UIPanel()
    {
    }

    void UIPanel::Render()
    {
        UIBase::Render();
    }
}
