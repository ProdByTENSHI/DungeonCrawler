#include "engine/world/WorldManager.hpp"
#include "engine/globals/Globals.hpp"
#include "engine/tenshiUtil/math/Vector2Int.hpp"
#include "engine/memory/RscManager.hpp"
#include "engine/tenshiUtil/vendor/tileson.hpp"

#include <spdlog/spdlog.h>
#include <algorithm>

namespace tenshi
{
    WorldManager::WorldManager()
    {
    }

    WorldManager::~WorldManager()
    {
        for (auto& s : m_WorldSections)
        {
            UnloadWorldSection(s.first);
        }
    }

    void WorldManager::LoadWorldSection(u16 id)
    {
        if (m_CurrentSection)
            UnloadWorldSection(m_CurrentSection->m_Id);

        // Load Section from LRU if it is still in cache
        auto _it = std::find(m_WorldSectionLRU.begin(), m_WorldSectionLRU.end(), id);
        if (_it != m_WorldSectionLRU.end())
        {
            m_CurrentSection = m_WorldSections[*_it];
            return;
        }

        // Load Section from Disk
        // -- Load File
        std::ifstream file(WORLD_MANIFEST_PATH);
        if (!file.is_open())
            throw std::runtime_error("Could not open World Manifest!");

        json j;
        file >> j;

        for (auto& s : j["sections"])
        {
            if (GetValue<u16>(s, "id") != id)
                continue;

            WorldSection* section = new WorldSection();
            section->m_Id = GetValue<u16>(s, "id");
            section->m_Name = GetValue<std::string>(s, "name");
            section->m_NSWE = static_cast<NSWE>(GetValue<u8>(s, "nswe"));
            section->m_X = GetValue<u8>(s, "x");
            section->m_Y = GetValue<u8>(s, "y");
            section->m_Description = GetValue<std::string>(s, "description");

            WorldSectionData* data =
                LoadWorldSectionData(*section, GetValue<std::string>(s, "map"));
            if (!data)
            {
                throw std::runtime_error("Could not load World Section");
            }

            AddWorldSection(section, data);
        }
    }

    void WorldManager::LoadWorldSection(const std::string& name)
    {
        // Load from Disk
        // -- Load File
        std::ifstream file(WORLD_MANIFEST_PATH);
        if (!file.is_open())
            throw std::runtime_error("Could not open World Manifest!");

        json j;
        file >> j;

        u16 _id = 0;

        for (auto& s : j["sections"])
        {
            if (GetValue<std::string>(s, "name") != name)
                continue;

            WorldSection* section = new WorldSection();
            section->m_Id = GetValue<u16>(s, "id");
            section->m_Name = GetValue<std::string>(s, "name");
            section->m_NSWE = static_cast<NSWE>(GetValue<u8>(s, "nswe"));
            section->m_X = GetValue<u8>(s, "x");
            section->m_Y = GetValue<u8>(s, "y");
            section->m_Description = GetValue<std::string>(s, "description");

            _id = section->m_Id;

            WorldSectionData* data =
                LoadWorldSectionData(*section, GetValue<std::string>(s, "map"));
            if (!data)
            {
                throw std::runtime_error("Could not load World Section");
            }

            AddWorldSection(section, data);
            m_CurrentSection = section;
        }
    }

    void WorldManager::UnloadWorldSection(u16 id)
    {
        // TODO: Implement
    }

    WorldSection* WorldManager::GetWorldSection(u16 id)
    {
        for (auto& section : m_WorldSections)
        {
            if (section.first == id)
                return section.second;
        }

        throw std::runtime_error("Could not Get World Section");
    }

    WorldSectionData* WorldManager::GetWorldSectionData(u16 id)
    {
        for (auto& section : m_WorldSections)
        {
            if (section.first == id)
                return section.second->m_Data;
        }

        throw std::runtime_error("Could not get World Section");
    }

    void WorldManager::Update()
    {
    }

    void WorldManager::Render()
    {
        for (auto& layer : m_CurrentSection->m_Data->m_Data)
        {
            for (auto& tile : layer->m_RenderTiles)
            {
                RenderCommand _cmd;
                _cmd.m_TextureId = tile->m_TextureId;
                _cmd.m_DstRect = tile->m_DstRect;
                _cmd.m_SrcRect = tile->m_SrcRect;

                g_MasterRenderer->PushRenderCommand(layer->m_Layer, _cmd);
            }
        }

        for (auto& entry : m_CurrentSection->m_Data->m_Entries)
        {
            DrawRectGizmo(entry->m_BoundingBox, WHITE);
        }
    }

    void WorldManager::AddWorldSection(WorldSection* section, WorldSectionData* data)
    {
        if (!section || !data)
        {
            spdlog::error("Could not add World Section since it is invalid");
            throw std::runtime_error("Could not add World Section");
        }

        u8 _id = section->m_Id;

        section->m_Data = data;
        m_WorldSections[section->m_Id] = section;

        // If Cache Limit is reached:
        // Free the Section used the longest time ago
        if (m_WorldSectionLRU.size() + 1 >= SECTION_CACHE_SIZE)
        {
            spdlog::info("Section Cache Limit reached!");

            WorldSection* _toDelete = m_WorldSections[m_WorldSectionLRU.front()];
            m_WorldSectionLRU.erase(m_WorldSectionLRU.begin());
            m_WorldSectionLRU.push_back(section->m_Id);

            m_WorldSections.erase(_toDelete->m_Id);
            delete _toDelete;
        }
    }

    WorldSectionData* WorldManager::LoadWorldSectionData(WorldSection& section, const std::string& path)
    {
        WorldSectionData* data = new WorldSectionData();
        data->m_Id = section.m_Id;

        data->m_Data.push_back(new RenderLayerData(RenderLayer::Ground));
        data->m_Data.push_back(new RenderLayerData(RenderLayer::Water));
        data->m_Data.push_back(new RenderLayerData(RenderLayer::Entity));

        // -- Load Tile Map Data
        std::unique_ptr<tson::Map> map = tileson.parse(path.c_str());
        if (map->getStatus() == tson::ParseStatus::OK)
        {
            for (auto& layer : map->getLayers())
            {
                // Load Tiles
                if (layer.getType() == tson::LayerType::TileLayer)
                {
                    std::map<std::tuple<i32, i32>, tson::Tile*> tileData = layer.getTileData();

                    RenderLayerData& layerTileData = data->GetLayerData(RenderLayer::Ground);

                    std::string _lastTextureName = "";
                    u32 _lastTextureId = 0;

                    for (auto& [id, tile] : tileData)
                    {
                        Tile* _worldTile = new Tile();
                        RenderTile* _renderTile = new RenderTile();

                        tson::Vector2f _pos = tile->getPosition(id);
                        Vector2Int _tilePos = Vector2Int(_pos.x / TILE_SIZE, _pos.y / TILE_SIZE);

                        _worldTile->m_Position = _tilePos;

                        if (layer.getName() == "Collision")
                        {
                            _worldTile->m_IsSolid = true;
                        }

                        tson::Rect _srcRect = tile->getDrawingRect();

                        _renderTile->m_DstRect = {(f32)_tilePos.x * TILE_SIZE,
                            (f32)_tilePos.y * TILE_SIZE,
                            TILE_SIZE, TILE_SIZE};
                        _renderTile->m_SrcRect = {(f32)_srcRect.x,(f32)_srcRect.y,
                            (f32)_srcRect.width, (f32)_srcRect.height};

                        std::string _name = tile->getTileset()->getName();
                        if (_lastTextureName != _name)
                        {
                            _lastTextureName = _name.c_str();
                            bool _validTexture = false;

                            for (auto& tex : Textures::textureBinding)
                            {
                                if (tex.m_Name != _lastTextureName)
                                    continue;

                                _lastTextureId = *tex.m_Target;
                                _validTexture = true;
                            }

                            if (!_validTexture)
                            {
                                spdlog::error("Path: {}", _lastTextureName);
                                throw std::runtime_error("Could not load Tile Map because a Texture is missing");
                            }
                        }

                        _renderTile->m_TextureId = _lastTextureId;

                        layerTileData.m_Tiles.push_back(_worldTile);
                        layerTileData.m_RenderTiles.push_back(_renderTile);
                    }
                }
            }
        }

        // -- Load in Objects
        for (auto& objLayer : map->getLayers())
        {
            if (objLayer.getType() != tson::LayerType::ObjectGroup)
                continue;

            spdlog::info("Object Layer{}", objLayer.getName().c_str());

            // -- Entries
            if (objLayer.getName() == "Entries")
            {
                for (auto& entry : objLayer.getObjects())
                {
                    spdlog::info("Entry {}", entry.getName().c_str());
                    SectionEntry* sectionEntry = new SectionEntry();
                    sectionEntry->m_Id = entry.getId();
                    sectionEntry->m_NSWE_Dir = (NSWE)entry.getProp("Dir")->getValue<i32>();
                    sectionEntry->m_ConnectedSectionId = (u8)entry.getProp("Connected_Section")
                    ->getValue<i32>();
                    sectionEntry->m_BoundingBox.x = entry.getPosition().x;
                    sectionEntry->m_BoundingBox.y = entry.getPosition().y;
                    sectionEntry->m_BoundingBox.width = entry.getSize().x;
                    sectionEntry->m_BoundingBox.height = entry.getSize().y;
                    data->m_Entries.push_back(sectionEntry);
                }
            }

            // -- Entities
            if (objLayer.getName() == "Entity")
            {
                for (auto& entity : objLayer.getObjects())
                {
                    spdlog::info("Entity {}", entity.getName().c_str());
                }
            }
        }

        return data;
    }

    bool WorldManager::IsSectionInLRU(u16 id) const
    {
        if (std::find(m_WorldSectionLRU.begin(), m_WorldSectionLRU.end(), id)
            != m_WorldSectionLRU.end())
            return true;

        return false;
    }
}