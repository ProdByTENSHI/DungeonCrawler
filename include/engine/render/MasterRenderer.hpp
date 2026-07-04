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

        void PushRenderCommand(u8 layerId, RenderCommand cmd);
        void PushRenderCommandBuffer(u8 layerId, const std::vector<RenderCommand>& buffer);

        void PushDebugGizmo(DebugGizmo gizmo);

        void Render();

        u8 GetRenderLayerIdByName(const std::string& name) const;

    private:
        void StageRenderCmdBuffers();
        void RenderDrawCommandBuffer(const std::vector<RenderCommand>& buffer) const;

        bool DoesLayerBufferExist(RenderLayer layer) const;

    private:
        RenderTexture2D m_FinalOutputTexture;

        // Vector of Render Command Buffers split by Layer
        // Index matches internal Layer ID
        std::vector<std::vector<RenderCommand>> m_RenderCommands;

        // Translation Map which holds the indices to the Render Commands Buffer by their Layer Properties
        std::unordered_map<RenderLayer, size_t> m_RenderCommandsMap;

        std::vector<DebugGizmo> m_DebugGizmos;
    };
}
