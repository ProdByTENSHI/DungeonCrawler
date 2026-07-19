#pragma once

#include "UIComponentTypes.hpp"
#include "engine/render/RenderCommand.hpp"
#include "engine/tenshiUtil/math/Vector2Int.hpp"

namespace tenshi
{
    class UIBase
    {
    public:
        UIBase(u16 id, UIComponentType type);
        virtual ~UIBase() {}

        virtual RenderCommand GetRenderCommand() = 0;
        virtual void Update() = 0;

        void SetParent(UIBase* parent);
        void AddChild(UIBase* child);
        void RemoveChild(u16 id);

        void SetRelativeOffset(Vector2Int offset);
        void SetAbsoluteOffset(Vector2Int offset);
        void SetRelativeSize(Vector2Int size);
        void SetAbsoluteSize(Vector2Int size);

        void OnWindowResize();

        bool operator==(const UIBase& other) const
        {
            return m_Id == other.m_Id;
        }

    private:
        Vector2Int CalculateAbsoluteVector(Vector2Int relativeVec);
        Vector2Int CalculateRelativeVector(Vector2Int absoluteVec);

    public:
        const u16 m_Id;
        const UIComponentType m_Type;

        UIBase* m_Parent = nullptr;

        bool m_IsVisible = true;

        // At the Top Left
        Vector2 m_Position = {0,0};

        Vector2Int m_RelativeOffset = {0,0};
        Vector2Int m_AbsoluteOffset = {0,0};
        Vector2Int m_RelativeSize = {0,0};
        Vector2Int m_AbsoluteSize = {0,0};

        // Nullptr for Root
        std::vector<UIBase*> m_Children;

    };
}
