#pragma once
#include "UIBase.hpp"

namespace tenshi
{
    class UIText : public UIBase
    {
    public:
        UIText(u16 id, UIComponentType type = UIComponentType::Text);
        ~UIText() override;

        void SetText(const std::string& text);

    public:


    protected:
        std::string m_Text = "Text";
    };
}
