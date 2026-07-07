#include "game/projectiles/Projectile.hpp"

namespace tenshi
{
    Projectile::Projectile(u32 id, const std::string& name)
        : Entity(id, name)
    {
        m_HasLimitedLifeTime = true;
        m_TotalLifeTime = 4.0f;
    }

    Projectile::~Projectile()
    {
    }

    void Projectile::Update()
    {
        m_CurrentLifeTime += GetFrameTime();

        m_Position.x += m_Velocity.x * GetFrameTime();
        m_Position.y += m_Velocity.y * GetFrameTime();
    }

    RenderCommand Projectile::CreateRenderCommand()
    {
        RenderCommand _cmd;

        _cmd = m_Anim->GetRenderCommand();

        _cmd.m_DstRect = {m_Position.x, m_Position.y, m_Size.x, m_Size.y};
        _cmd.m_Rotation = m_Rotation;

        return _cmd;
    }
}