#pragma once

#include "engine/globals/Constants.hpp"
#include "engine/render/RenderCommand.hpp"
#include "engine/debug/DebugGizmo.hpp"

#include <raylib.h>
#include <vector>
#include <unordered_map>

namespace tenshi
{
    class MasterRenderer
    {
    public:
        MasterRenderer();

        ~MasterRenderer();

        void PushRenderCommand(RenderLayer layer, RenderCommand cmd);
        void PushRenderCommandBuffer(RenderLayer layer, const std::vector<RenderCommand>& buffer);

        void PushDebugGizmo(DebugGizmo gizmo);

        void Render();

    private:
        void StageRenderCmdBuffers();
        void RenderDrawCommandBuffer(const std::vector<RenderCommand>& buffer) const;

        std::vector<RenderCommand>& GetCommandBufferByLayer(RenderLayer layer);

    private:
        RenderTexture2D m_FinalOutputTexture;

        std::vector<RenderCommand> m_GroundRenderCommands;
        std::vector<RenderCommand> m_CollisionRenderCommands;
        std::vector<RenderCommand> m_EntityRenderCommands;
        std::vector<DebugGizmo> m_DebugGizmos;
    };
}
