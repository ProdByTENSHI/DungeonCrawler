#include "game/projectiles/Projectile.hpp"

#include "engine/globals/Globals.hpp"
#include "game/enemies/Enemy.hpp"
#include "game/player/Player.hpp"

namespace tenshi
{
    Projectile::Projectile(u32 id, const std::string& name, EntityType type, u32 shooterId)
        : Entity(id, name, type), m_ShooterId(shooterId)
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
        m_CurrentLifeTime += GetFrameTime();

        m_Position.x += m_Velocity.x * GetFrameTime();
        m_Position.y += m_Velocity.y * GetFrameTime();

        ResolveCollision();
    }

    RenderCommand Projectile::CreateRenderCommand()
    {
        DrawRectGizmo(GetBoundingBox(), GREEN);
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

        _rect.x = m_Position.x - (m_BoundingBoxSize.x * 0.5f);
        _rect.y = m_Position.y - (m_BoundingBoxSize.y * 0.5f);
        _rect.width = m_BoundingBoxSize.x;
        _rect.height = m_BoundingBoxSize.y;

        return _rect;
    }

    void Projectile::ResolveCollision()
    {
        // Check if Wall has been hit
        bool _wallCheck = g_WorldManager->CheckCollision(GetBoundingBox(), nullptr);
        if (_wallCheck)
        {
            m_Anim = g_RscManager->GetAnimation(Animations::Projectile_Impact_Small);
        }

        // Check if Entity has been hit
        bool _entityCheck = g_EntityManager->CheckCollision(GetBoundingBox(), &m_HitEntities);
        if (_entityCheck)
        {
            for (auto& e : m_HitEntities)
            {
                if (e->m_Id == m_ShooterId)
                    continue;

                switch (e->m_Type)
                {
                case EntityType::Enemy:
                    {
                        Enemy* enemy = dynamic_cast<Enemy*>(e);
                        enemy->Hit(m_Damage);
                        Die();
                        break;
                    }

                case EntityType::Player:
                    {
                        Player* player = dynamic_cast<Player*>(e);
                        player->Hit(m_Damage);
                        Die();
                        break;
                    }

                default:
                    break;
                }
            }
        }
    }

    void Projectile::Die()
    {
        spdlog::info("Destroyed Projectile!");
        g_EntityManager->DestroyEntity(*this);
    }
}
