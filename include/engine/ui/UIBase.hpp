#pragma once

#include "UIComponentTypes.hpp"
#include "engine/graphics/SpriteSheet.hpp"
#include "engine/graphics/Sprite.hpp"
#include "engine/render/RenderCommand.hpp"
#include "engine/tenshiUtil/math/Vector2Int.hpp"

namespace tenshi
{
    class UIBase
    {
    public:
        UIBase(u16 id, UIComponentType type);
        virtual ~UIBase() {}

        virtual RenderCommand Render();
        virtual void Update() {}

        void SetParent(UIBase* parent);
        void AddChild(UIBase* child);
        void RemoveChild(u16 id);

        void SetRelativeOffset(Vector2 offset);
        void SetAbsoluteOffset(Vector2 offset);
        void SetRelativeSize(Vector2 size);
        void SetAbsoluteSize(Vector2 size);

        void SetColor(Color c);

        void OnWindowResize();

        bool operator==(const UIBase& other) const
        {
            return m_Id == other.m_Id;
        }

    private:
        Vector2 CalculateAbsoluteVector(Vector2 relVec) const;

        // Relative Values are stored between 0.0 and 1.0
        Vector2 CalculateRelativeVector(Vector2 absVec) const;

    public:
        const u16 m_Id;
        const UIComponentType m_Type;

        UIBase* m_Parent = nullptr;

        bool m_IsVisible = true;

        Sprite* m_Sprite = nullptr;

        // At the Top Left
        Vector2 m_Position = {0,0};

        Vector2 m_RelativeOffset = {0,0};
        Vector2 m_AbsoluteOffset = {0,0};
        Vector2 m_RelativeSize = {0,0};
        Vector2 m_AbsoluteSize = {0,0};

        Color m_Color = WHITE;

        // Nullptr for Root
        std::vector<UIBase*> m_Children;

    };
}
