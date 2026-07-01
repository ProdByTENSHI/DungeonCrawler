#include "engine/globals/Globals.hpp"
#include "engine/globals/GlobalEvents.hpp"
#include "engine/render/MasterRenderer.hpp"

namespace tenshi
{
    MasterRenderer::MasterRenderer()
        : m_FinalOutputTexture(LoadRenderTexture(RENDER_TEXTURE_SIZE.x, RENDER_TEXTURE_SIZE.y))
    {
    }

    MasterRenderer::~MasterRenderer()
    {
    }

    void MasterRenderer::Render()
    {
        BeginTextureMode(m_FinalOutputTexture);

        BeginMode2D(g_MainCam->m_Camera);
        OnRender.Dispatch();

        StageRenderCmdBuffers();

        RenderDrawCommandBuffer(m_GroundRenderCommands);
        RenderDrawCommandBuffer(m_WaterRenderCommands);
        RenderDrawCommandBuffer(m_EntityRenderCommands);

        ClearBackground(GRAY);

        EndMode2D();

        // -- RENDER UI HERE LATER

        // -- Render Debug
        if (g_IsInDebugMode)
        {
            for (DebugGizmo g : m_DebugGizmos)
            {
                switch (g.m_Type)
                {
                case GizmoType::Rectangle:
                    DrawRectangleLines(g.m_BoundingBox.x, g.m_BoundingBox.y,
                        g.m_BoundingBox.width, g.m_BoundingBox.height, g.m_Color);
                    break;

                case GizmoType::Circle:
                    DrawCircleLines(g.m_BoundingBox.x, g.m_BoundingBox.y, g.m_BoundingBox.x, g.m_Color);
                    break;
                }
            }
        }

        EndTextureMode();

        BeginDrawing();

        DrawTexturePro(m_FinalOutputTexture.texture,
            {0,-RENDER_TEXTURE_SIZE.y,RENDER_TEXTURE_SIZE.x, -RENDER_TEXTURE_SIZE.y},
            {0,0,(f32)g_WindowWidth, (f32)g_WindowHeight},
            {0,0}, 0.0f, WHITE);

        EndDrawing();

        m_GroundRenderCommands.clear();
        m_EntityRenderCommands.clear();
        m_DebugGizmos.clear();
    }

    void MasterRenderer::PushRenderCommand(RenderLayer layer, RenderCommand cmd)
    {
        GetCommandBufferByLayer(layer).push_back(cmd);
    }

    void MasterRenderer::PushRenderCommandBuffer(RenderLayer layer, const std::vector<RenderCommand>& buffer)
    {
        std::vector<RenderCommand>& _cmd = GetCommandBufferByLayer(layer);
        _cmd.insert(_cmd.end(), buffer.begin(), buffer.end());
    }

    void MasterRenderer::PushDebugGizmo(DebugGizmo gizmo)
    {
        m_DebugGizmos.push_back(gizmo);
    }

    void MasterRenderer::StageRenderCmdBuffers()
    {
        // -- Sort Render Command Buffers
        std::sort(m_GroundRenderCommands.begin(), m_GroundRenderCommands.end());
        std::sort(m_EntityRenderCommands.begin(), m_EntityRenderCommands.end());
    }

    std::vector<RenderCommand>& MasterRenderer::GetCommandBufferByLayer(RenderLayer layer)
    {
        switch (layer)
        {
        case RenderLayer::Ground:
            return m_GroundRenderCommands;

        case RenderLayer::Water:
            return m_WaterRenderCommands;

        case RenderLayer::Entity:
            return m_EntityRenderCommands;
        }

        return m_EntityRenderCommands;
    }

    void MasterRenderer::RenderDrawCommandBuffer(const std::vector<RenderCommand>& buffer) const
    {
        i32 _lastTextureId = -1;
        SpriteSheet* _spriteSheet = nullptr;
        Texture2D _texture;

        for (i32 i = 0; i < buffer.size(); i++)
        {
            RenderCommand _cmd = buffer[i];
            if (_lastTextureId != _cmd.m_TextureId)
            {
                _lastTextureId = _cmd.m_TextureId;
                _spriteSheet = g_RscManager->GetSpritesheet(_lastTextureId);
                _texture = *g_RscManager->GetTexture(_spriteSheet->GetTexture());
            }

            DrawTextureRec(_texture, _cmd.m_SrcRect,
                {_cmd.m_DstRect.x, _cmd.m_DstRect.y}, WHITE);
        }
    }
}
