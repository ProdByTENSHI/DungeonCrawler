#pragma once
#include "UIBase.hpp"

namespace tenshi
{
    class UIPanel : public UIBase
    {
    public:
        UIPanel(u16 id, UIComponentType type = UIComponentType::Panel);
        ~UIPanel();

        RenderCommand GetRenderCommand() override;
        void Update() override;

        void SetColor(Color color);

    protected:

    };
}
