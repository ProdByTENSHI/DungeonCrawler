#include "engine/globals/Globals.hpp"
#include "engine/globals/GlobalEvents.hpp"
#include "engine/render/MasterRenderer.hpp"

namespace tenshi
{
    MasterRenderer::MasterRenderer()
        : m_FinalOutputTexture(LoadRenderTexture(VIEWPORT_SIZE.x, VIEWPORT_SIZE.y))
    {
        // TODO: Update this when resizing the Window
        m_RenderScaling.x = g_WindowWidth / VIEWPORT_SIZE.x;
        m_RenderScaling.y = g_WindowHeight / VIEWPORT_SIZE.y;
    }

    MasterRenderer::~MasterRenderer()
    {
    }

    void MasterRenderer::Render()
    {
        BeginTextureMode(m_FinalOutputTexture);

        ClearBackground(GRAY);

        BeginMode2D(g_MainCam->m_Camera);
        OnRenderEvent.Dispatch();

        StageRenderCmdBuffers();

        for (i32 i = 0; i < m_RenderCommands.size(); i++)
        {
            RenderDrawCommandBuffer(m_RenderCommands[i]);
        }

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
                    DrawCircleLines(g.m_BoundingBox.x, g.m_BoundingBox.y, g.m_BoundingBox.width, g.m_Color);
                    break;
                }
            }
        }

        EndMode2D();

        // -- RENDER UI HERE LATER
        OnUiRenderEvent.Dispatch();

        EndTextureMode();

        BeginDrawing();

        DrawTexturePro(m_FinalOutputTexture.texture,
            {0,-VIEWPORT_SIZE.y,VIEWPORT_SIZE.x, -VIEWPORT_SIZE.y},
            {0,0,(f32)g_WindowWidth, (f32)g_WindowHeight},
            {0,0}, 0.0f, WHITE);

        EndDrawing();

        for (i32 i = 0; i < m_RenderCommands.size(); i++)
        {
            m_RenderCommands[i].clear();
        }

        m_DebugGizmos.clear();
    }

    void MasterRenderer::CreateRenderLayerBuffer(RenderLayer layer)
    {
        static u32 _callCount = 0;
        ++_callCount;
        spdlog::info("Render Layer Buffer {} : {}", layer.m_Name, _callCount);

        std::vector<RenderCommand> _buffer;
        m_RenderCommands.push_back(_buffer);
        m_RenderCommandsMap.insert({layer, m_RenderCommands.size() - 1});
    }

    u8 MasterRenderer::GetRenderLayerIdByName(const std::string& name) const
    {
        for (auto& layer : m_RenderCommandsMap)
        {
            if (layer.first.m_Name == name)
                return layer.first.m_Id;
        }

        spdlog::warn("No Layer with Name {} was found", name);
        return 0xFF;
    }

    void MasterRenderer::PushRenderCommand(u8 layerId, RenderCommand cmd)
    {
        m_RenderCommands[layerId].push_back(cmd);
    }

    void MasterRenderer::PushRenderCommandBuffer(u8 layerId, const std::vector<RenderCommand>& buffer)
    {
        std::vector<RenderCommand>& _cmd = m_RenderCommands[layerId];
        _cmd.insert(_cmd.end(), buffer.begin(), buffer.end());
    }

    void MasterRenderer::PushDebugGizmo(DebugGizmo gizmo)
    {
        m_DebugGizmos.push_back(gizmo);
    }

    void MasterRenderer::StageRenderCmdBuffers()
    {
        // -- Sort Render Command Buffers
        for (i32 i = 0; i < m_RenderCommands.size(); i++)
        {
            std::sort(m_RenderCommands[i].begin(), m_RenderCommands[i].end());
        }
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
            //
            // DrawTextureRec(_texture, _cmd.m_SrcRect,
            //     {_cmd.m_DstRect.x, _cmd.m_DstRect.y}, _cmd.m_Color);
            DrawTexturePro(_texture, _cmd.m_SrcRect, _cmd.m_DstRect,
                _cmd.m_Origin, _cmd.m_Rotation, _cmd.m_Color);
        }
    }

    bool MasterRenderer::DoesLayerBufferExist(RenderLayer layer) const
    {
        return m_RenderCommandsMap.find(layer) != m_RenderCommandsMap.end();
    }
}
