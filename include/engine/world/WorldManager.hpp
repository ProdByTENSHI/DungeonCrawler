#pragma once

#include "engine/world/WorldSection.hpp"
#include "engine/tenshiUtil/io/json.hpp"
#include "engine/tenshiUtil/vendor/tileson.hpp"
#include "WorldSectionData.hpp"

#include <unordered_map>
#include <vector>

namespace tenshi
{
    class WorldManager
    {
    public:
        WorldManager();
        ~WorldManager();

        // -- Cache Operations of World Sections
        void LoadWorldSection(u16 id);
        void LoadWorldSection(const std::string& name);
        void UnloadWorldSection(u16 id);

        WorldSection* GetWorldSection(u16 id);
        WorldSectionData* GetWorldSectionData(u16 id);

        // bbox: Bounding Box to check against
        // collider: Vector of Rectangle the Bounding Box collided with
        bool CheckCollision(Rectangle bbox, std::vector<Rectangle>* colliders) const;

        // -- Game Flow
        void Update();
        void Render();

        // -- Util
        Vector2 GetSectionSize() const
        {
            if (!m_CurrentSection)
                return {0.0f,0.0f};

            return m_CurrentSection->m_Data->m_SectionSize;
        }

        // Returns the Render Tile on this Position of the Layer
        // By default the Layer is 0 = Ground Layer
        RenderTile* GetRenderTile(Vector2Int pos, u8 layer = 0);

        // Returns the Tile on this Position of the Layer
        // By default the Layer is 0 = Ground Layer
        Tile* GetTile(Vector2Int pos, u8 layer = 0);

    private:
        void AddWorldSection(WorldSection* section, WorldSectionData* data);
        WorldSectionData* LoadWorldSectionData(WorldSection& section, const std::string& path);

        bool IsSectionInLRU(u16 id) const;

        template <typename T>
        static T GetValue(const nlohmann::json& j, const char* key)
        {
            T _value;

            if (!j.contains(key))
                throw std::runtime_error(std::string("Missing Key in Manifest: ") + key);

            return j[key].get<T>();
        }

    private:
        const std::string WORLD_MANIFEST_PATH = "World/World_Manifest.json";

        // Preload 4 Sections with their 4 adjacent Sections
        const u8 SECTION_CACHE_SIZE = 4 * 4;

        //-- World Sections LRU(Least Recently Used)
        std::unordered_map<u16, WorldSection*> m_WorldSections;

        std::vector<u16> m_WorldSectionLRU;

        // Section Player is currently in
        WorldSection* m_CurrentSection = nullptr;

        // The Section to the West, East, North and South are also loaded and updated
        // Not every Section has 4 adjacent Section which means a Null Check has to be performed before usage
        WorldSection* m_NeighbourSections[4] = {};

        tson::Tileson tileson;
    };
}
