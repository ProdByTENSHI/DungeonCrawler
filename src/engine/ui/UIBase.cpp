#include "engine/ui/UIBase.hpp"
#include "engine/globals/Globals.hpp"

namespace tenshi
{
    UIBase::UIBase(u16 id, UIComponentType type)
        : m_Id(id), m_Type(type)
    {
    }

    void UIBase::SetParent(UIBase* parent)
    {
        if (parent == m_Parent)
            return;

        m_Parent = parent;
        m_Parent->AddChild(this);

        SetRelativeOffset(m_RelativeOffset);
        SetRelativeSize(m_RelativeSize);
    }

    void UIBase::AddChild(UIBase* child)
    {
        for (auto& c : m_Children)
        {
            if (child == c)
                return;
        }

        m_Children.push_back(child);
    }

    void UIBase::RemoveChild(u16 id)
    {
        for (auto& c : m_Children)
        {
            if (c->m_Id != id)
                continue;

            m_Children.erase(m_Children.begin() + id);
            c->SetParent(nullptr);
        }
    }

    void UIBase::SetRelativeOffset(Vector2Int offset)
    {
        m_RelativeOffset = offset;
        m_AbsoluteOffset = CalculateAbsoluteVector(m_RelativeOffset);

        if (!m_Parent) {
            m_Position = {(f32)m_AbsoluteOffset.x, (f32)m_AbsoluteOffset.y};
        } else
        {
            m_Position = {(f32)m_AbsoluteOffset.x + g_WindowWidth,
                (f32)m_AbsoluteOffset.y + g_WindowHeight};
        }
    }

    void UIBase::SetAbsoluteOffset(Vector2Int offset)
    {
        m_AbsoluteOffset = offset;
        m_RelativeOffset = CalculateRelativeVector(m_AbsoluteOffset);
    }

    void UIBase::SetRelativeSize(Vector2Int size)
    {
        m_RelativeSize = CalculateRelativeVector(size);
        m_AbsoluteSize = CalculateAbsoluteVector(m_RelativeSize);
    }

    void UIBase::SetAbsoluteSize(Vector2Int size)
    {
        m_AbsoluteSize = CalculateAbsoluteVector(size);
        m_RelativeSize = CalculateRelativeVector(m_AbsoluteSize);
    }

    Vector2Int UIBase::CalculateAbsoluteVector(Vector2Int relativeVec)
    {
        Vector2Int _absOffset = {0, 0};

        if (!m_Parent)
        {
            Vector2Int _scrSize = {g_WindowWidth, g_WindowHeight};
            _absOffset.x = (_scrSize.x / relativeVec.x);
            _absOffset.y = (_scrSize.y / relativeVec.y);
        } else
        {
            _absOffset.x = (m_Parent->m_AbsoluteSize.x / relativeVec.x);
            _absOffset.y = (m_Parent->m_AbsoluteSize.y / relativeVec.y);
        }

        return _absOffset;
    }

    Vector2Int UIBase::CalculateRelativeVector(Vector2Int absoluteVec)
    {
        Vector2Int _relOffset = {0, 0};

        if (!m_Parent)
        {
            Vector2Int _scrSize = {g_WindowWidth, g_WindowHeight};
            _relOffset.x = (absoluteVec.x / _scrSize.x) * 100;
            _relOffset.y = (absoluteVec.y / _scrSize.y) * 100;
        } else
        {
            _relOffset.x = (absoluteVec.x / m_Parent->m_AbsoluteSize.y) * 100;
            _relOffset.y = (absoluteVec.y / m_Parent->m_AbsoluteSize.y) * 100;
        }

        return _relOffset;
    }

    void UIBase::OnWindowResize()
    {
        SetAbsoluteOffset({g_WindowWidth, g_WindowHeight});
    }
}
