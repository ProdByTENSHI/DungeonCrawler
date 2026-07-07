#include "game/projectiles/Projectile.hpp"

#include "engine/globals/Globals.hpp"

namespace tenshi
{
    Projectile::Projectile(u32 id, const std::string& name, u32 shooterId)
        : Entity(id, name), m_ShooterId(shooterId)
    {
        m_HasLimitedLifeTime = true;
        m_TotalLifeTime = 4.0f;

        m_HitEntities.reserve(8);
    }

    Projectile::~Projectile()
    {
    }

    void Projectile::Update()
    {
        if (m_HasHit)
        {

        }

        m_CurrentLifeTime += GetFrameTime();

        m_Position.x += m_Velocity.x * GetFrameTime();
        m_Position.y += m_Velocity.y * GetFrameTime();

        // Check if Wall has been hit
        bool _wallCheck = g_WorldManager->CheckCollision(GetBoundingBox(), nullptr);
        if (_wallCheck)
        {
            m_HasHit = true;
            m_Anim = g_RscManager->GetAnimation(Animations::Projectile_Impact_Small);
        }

        // Check if Entity has been hit
        bool _entityCheck = g_EntityManager->CheckCollision(GetBoundingBox(), &m_HitEntities);
        if (_entityCheck)
        {
            for (auto& e : m_HitEntities)
            {
                if (e->m_Id)
            }
        }
    }

    RenderCommand Projectile::CreateRenderCommand()
    {
        RenderCommand _cmd;

        _cmd = m_Anim->GetRenderCommand();

        _cmd.m_DstRect = {m_Position.x, m_Position.y, m_Size.x, m_Size.y};
        _cmd.m_Rotation = m_Rotation;
        _cmd.m_Origin = {m_Size.x * 0.5f, m_Size.y * 0.5f};

        return _cmd;
    }

    Rectangle Projectile::GetBoundingBox() const
    {
        Rectangle _rect;

        _rect.x = m_Position.x;
        _rect.y = m_Position.y;
        _rect.width = m_Size.x;
        _rect.height = m_Size.y;

        return _rect;
    }

    void Projectile::ResolveCollision()
    {
        Rectangle _boundingBox = {m_Position.x, m_Position.y, m_Size.x, m_Size.y};

    }
}
