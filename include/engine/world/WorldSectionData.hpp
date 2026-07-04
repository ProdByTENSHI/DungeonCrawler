#pragma once

#include <stdexcept>
#include <vector>
#include <unordered_map>

#include "engine/tenshiUtil/Types.hpp"
#include "engine/world/Tile.hpp"
#include "engine/world/NSWE.hpp"
#include "engine/entities/Entity.hpp"

#include "engine/globals/Constants.hpp"
#include "spdlog/spdlog.h"

namespace tenshi
{
    // Data for a Tile Map Render Layer
    struct RenderLayerData
    {
        explicit RenderLayerData(RenderLayer layer) : m_Layer(layer)
        {
        }

        RenderLayer m_Layer;
        std::vector<Tile*> m_Tiles;
        std::vector<RenderTile*> m_RenderTiles;

        RenderTile* GetRenderTile(Tile* tile)
        {
            RenderTile* ret = nullptr;
            for (i32 i = 0; i < m_Tiles.size(); i++)
            {
                if (m_Tiles[i] != tile)
                    continue;

                ret = m_RenderTiles[i];
            }

            if (!ret)
                spdlog::warn("Could not get Render Tile for Tile {} {} on Layer {}",
                    tile->m_Position.x, tile->m_Position.y, m_Layer.m_Name);

            return ret;
        }

        bool operator==(const RenderLayerData& rhs) const
        {
            return m_Layer == rhs.m_Layer;
        }
    };

    // Data for a Object Render Layer
    struct ObjectLayerData
    {
        explicit ObjectLayerData(RenderLayer layer) : m_Layer(layer) {}

        RenderLayer m_Layer;

        bool operator==(const ObjectLayerData& rhs) const
        {
            return m_Layer == rhs.m_Layer;
        }
    };

    // When a Player enters a SectionEntry he will travel to the Section
    // the current Section is connected to
    struct SectionEntry
    {
        u8 m_Id = 0;

        // Where is the Entry leading to
        NSWE m_NSWE_Dir;

        // ID of the Section it leads to
        u16 m_ConnectedSectionId;

        Rectangle m_BoundingBox;
    };

    // Holds the actual Section Data
    struct WorldSectionData
    {
        // Id corresponds to the WorldSection ID it is linked to
        u16 m_Id = 0;

        Vector2 m_SectionSize = {0.0f, 0.0f};

        std::vector<RenderLayerData*> m_TileData;
        std::vector<ObjectLayerData*> m_ObjectData;
        std::vector<SectionEntry*> m_Entries;
        std::vector<Entity*> m_Entities;

        RenderLayerData& GetLayerData(RenderLayer layer)
        {
            for (auto& data : m_TileData)
            {
                if (data->m_Layer == layer)
                    return *data;
            }

            throw std::runtime_error("Could not get Layer Data for Layer");
        }

        bool operator==(const WorldSectionData& rhs) const
        {
            return m_Id == rhs.m_Id;
        }
    };
}
