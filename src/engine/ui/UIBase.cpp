#include "engine/ui/UIBase.hpp"
#include "engine/globals/Globals.hpp"

namespace tenshi
{
    UIBase::UIBase(u16 id, UIComponentType type)
        : m_Id(id), m_Type(type)
    {
    }

    void UIBase::Render()
    {
        RenderCommand _cmd;

        _cmd.m_DstRect = {m_Position.x, m_Position.y,
            m_AbsoluteSize.x, m_AbsoluteSize.y};
        _cmd.m_SrcRect = {(f32)m_AbsoluteSize.x, (f32)m_AbsoluteSize.y};
        _cmd.m_Color = m_Color;
        _cmd.m_Origin = {m_Position.x, m_Position.y};

        g_MasterRenderer->PushRenderCommand(RenderLayers::UI, _cmd);
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

    void UIBase::SetRelativeOffset(Vector2 offset)
    {
        m_RelativeOffset = offset;
        m_AbsoluteOffset = CalculateAbsoluteVector(m_RelativeOffset);

        if (!m_Parent) {
            m_Position = {m_AbsoluteOffset.x, m_AbsoluteOffset.y};
        } else
        {
            m_Position = {m_AbsoluteOffset.x + static_cast<f32>(g_WindowWidth),
                m_AbsoluteOffset.y + static_cast<f32>(g_WindowHeight)};
        }
    }

    void UIBase::SetAbsoluteOffset(Vector2 offset)
    {
        m_AbsoluteOffset = offset;
        m_RelativeOffset = CalculateRelativeVector(m_AbsoluteOffset);
    }

    void UIBase::SetRelativeSize(Vector2 size)
    {
        m_RelativeSize = size;
        m_AbsoluteSize = CalculateAbsoluteVector(m_RelativeSize);
    }

    void UIBase::SetAbsoluteSize(Vector2 size)
    {
        m_AbsoluteSize = size;
        m_RelativeSize = CalculateRelativeVector(m_AbsoluteSize);
    }

    void UIBase::SetColor(Color c)
    {
        m_Color = c;
    }

    Vector2 UIBase::CalculateAbsoluteVector(Vector2 relVec) const
    {
        Vector2 _absVal = {0, 0};

        if (!m_Parent)
        {
            Vector2 _scrSize = {VIEWPORT_SIZE.x, VIEWPORT_SIZE.y};
            _absVal.x = _scrSize.x * relVec.x;
            _absVal.y = _scrSize.y * relVec.y;
        } else
        {
            _absVal.x = m_Parent->m_AbsoluteSize.x * relVec.x;
            _absVal.y = m_Parent->m_AbsoluteSize.y * relVec.y;
        }

        return _absVal;
    }

    Vector2 UIBase::CalculateRelativeVector(Vector2 absVec) const
    {
        Vector2 _relVal = {0, 0};

        if (!m_Parent)
        {
            Vector2 _scrSize = {VIEWPORT_SIZE.x, VIEWPORT_SIZE.y};
            _relVal.x = absVec.x / _scrSize.x;
            _relVal.y = absVec.y / _scrSize.y;
        } else
        {
            _relVal.x = absVec.x / m_Parent->m_AbsoluteSize.x;
            _relVal.y = absVec.y / m_Parent->m_AbsoluteSize.y;
        }

        return _relVal;
    }

    void UIBase::OnWindowResize()
    {
        SetAbsoluteOffset({static_cast<f32>(g_WindowWidth),
            static_cast<f32>(g_WindowHeight)});
    }
}
