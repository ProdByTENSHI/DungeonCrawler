#pragma once
#include "UIBase.hpp"

namespace tenshi
{
    class UIPanel : public UIBase
    {
    public:
        UIPanel(u16 id, UIComponentType type = UIComponentType::Panel);
        ~UIPanel() override;

        void Render() override;

    protected:

    };
}
