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

    RenderCommand UIPanel::Render()
    {
        RenderCommand _cmd = UIBase::Render();
        return _cmd;
    }
}
