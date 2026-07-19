#pragma once

#include "engine/tenshiUtil/Types.hpp"

#include <raylib.h>

namespace tenshi
{
    constexpr f32 TILE_SIZE = 32.0f;
    const Vector2 VIEWPORT_SIZE = Vector2(480,320);

    enum class RenderLayers : u8
    {
        Ground = 0,
        Decoration = 1,
        Entities = 2,

        UI = 0xFE
    };

    struct RenderLayer
    {
        RenderLayer() {}
        explicit RenderLayer(RenderLayers id, const std::string& name)
            : m_Id(id), m_Name(name) {}

        const RenderLayers m_Id = RenderLayers::Ground;
        const std::string m_Name = "Undefined Layer";

        bool operator==(const RenderLayer& rhs) const
        {
            return m_Id == rhs.m_Id;
        }

        bool operator<(const RenderLayer& rhs) const
        {
            return (u8)m_Id < (u8)rhs.m_Id;
        }
    };
}

template <>
struct std::hash<tenshi::RenderLayer>
{
    std::size_t operator()(const tenshi::RenderLayer& layer) const noexcept
    {
        return std::hash<u8>()(std::hash<u32>()((u8)layer.m_Id));
    }
};