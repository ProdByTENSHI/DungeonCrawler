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

        void PushRenderCommand(RenderLayers layerId, RenderCommand cmd);
        void PushRenderCommandBuffer(u8 layerId, const std::vector<RenderCommand>& buffer);

        void PushDebugGizmo(DebugGizmo gizmo);

        void Render();

        void CreateRenderLayerBuffer(RenderLayer layer);
        RenderLayers GetRenderLayerIdByName(const std::string& name) const;

    public:
        // Holds the Scaling applied when drawing the final Texture
        Vector2 m_RenderScaling = {0.0f, 0.0f};

    private:
        void StageRenderCmdBuffers();
        void RenderDrawCommandBuffer(const std::vector<RenderCommand>& buffer) const;

        void DrawUI() const;

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
