#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <raylib.h>
#include <spdlog/spdlog.h>
#include <functional>

#include "engine/tenshiUtil/Types.hpp"
#include "engine/graphics/SpriteSheet.hpp"
#include "engine/globals/Constants.hpp"
#include "engine/graphics/Animation.hpp"
#include "engine/graphics/Sprite.hpp"
#include "engine/tenshiUtil/io/json.hpp"

using json = nlohmann::json;

// Used for Rsc Key Lookup
// Manifest ID Strings get hashed to a u32 for better Look up
// We store a LUT to map the Names to the IDs
enum class RscType : u8
{
    Texture,
    SpriteSheet,
    Sprite, // A Frame in a Sprite Sheet
    Animation,
    Sound,
    Music,
    Font
};

struct RscKey
{
    RscKey()
    {
    }

    RscKey(RscType type, u32 id)
        : m_Type(type), m_Id(id)
    {
    }

    RscType m_Type = RscType::Texture;
    u32 m_Id = 1337;

    bool operator==(const RscKey& rhs) const
    {
        return (m_Type == rhs.m_Type) && (m_Id == rhs.m_Id);
    }
};

template <>
struct std::hash<RscKey>
{
    std::size_t operator()(const RscKey& key) const noexcept
    {
        return std::hash<u8>()((u8)key.m_Type) ^ (std::hash<u32>()(key.m_Id) << 1);
    }
};

namespace tenshi
{
#pragma region Assets
    struct AssetBinding
    {
        AssetBinding()
        {
        }

        AssetBinding(const char* name, u32* target)
            : m_Name(name), m_Target(target)
        {
        }

        const char* m_Name = "";
        u32* m_Target = nullptr;
    };

    // We Populate the Asset IDs during Loading
    namespace Textures
    {
        inline u32 Tileset_1;
        inline u32 Player;
        inline u32 Enemies;
        inline u32 Projectiles;

        inline AssetBinding textureBinding[] = {
            {"Tileset_1", &Textures::Tileset_1},
            {"Player", &Textures::Player},
            {"Enemies", &Textures::Enemies},
            {"Projectiles", &Textures::Projectiles}
        };
    }

    namespace SpriteSheets
    {
        inline u32 Tileset_1;
        inline u32 Player;
        inline u32 Enemies;
        inline u32 Projectiles;

        inline AssetBinding spriteSheetBinding[] = {
            {"Tileset_1", &SpriteSheets::Tileset_1},
            {"Player", &SpriteSheets::Player},
            {"Enemies", &SpriteSheets::Enemies},
            {"Projectiles", &SpriteSheets::Projectiles}
        };
    }

    namespace Animations
    {
        inline u32 Player_Idle;
        inline u32 Player_Run;
        inline u32 Player_Shoot;
        inline u32 Player_Reload;
        inline u32 Player_Die;

        inline u32 Projectile_Laser;
        inline u32 Projectile_Impact_Small;

        inline u32 Drone_Idle;
        inline u32 Drone_Hit;
        inline u32 Drone_Die;

        inline AssetBinding animBinding[] = {
            {"Player_Idle", &Animations::Player_Idle},
            {"Player_Run", &Animations::Player_Run},
            {"Player_Shoot", &Animations::Player_Shoot},
            {"Player_Reload", &Animations::Player_Reload},
            {"Projectile_Laser", &Animations::Projectile_Laser},
            {"Projectile_Impact_Small", &Animations::Projectile_Impact_Small},
            {"Drone_Idle", &Animations::Drone_Idle},
            {"Drone_Hit", &Animations::Drone_Hit},
            {"Drone_Die", &Animations::Drone_Die},
        };
    }

#pragma endregion

    class RscManager
    {
    public:
        RscManager();

        // Load Assets from AssetsManifest.json File
        void LoadAssets();

        Texture2D* GetTexture(u32 id);
        SpriteSheet* GetSpritesheet(u32 id);
        Animation* GetAnimation(u32 id);

    private:
        // Returns the ID of the Texture
        u32 LoadTex(const std::string& id, const std::string& path);
        u32 LoadSprite(const std::string& id,
            u32 spriteSheetId, Rectangle srcRect);
        u32 LoadSpriteSheet(const std::string& id, u32 textureId,
                            u32 fWidth, u32 fHeight);
        u32 LoadAnimation(const std::string& id, u32 ssheetId,
                          f32 interval, std::vector<Rectangle> frames);

        void PopulateAssetBindings(RscType type);

        template <typename T>
        static T GetValue(const json& j, const char* key)
        {
            T _value;

            if (!j.contains(key))
                throw std::runtime_error(std::string("Missing Key in Manifest: ") + key);

            return j[key].get<T>();
        }

    private:
        const std::string ASSETS_MANIFEST_PATH = "Assets/AssetsManifest.json";

        std::vector<Texture2D*> m_TextureCache;
        std::vector<Sprite*> m_SpriteCache;
        std::vector<SpriteSheet*> m_SpriteSheetCache;
        std::vector<Animation*> m_AnimCache;

        // Only use this for Initial Asset Loading + Debug
        std::unordered_map<std::string, u32> m_TexStrToId;
        std::unordered_map<std::string, u32> m_SpriteStrToId;
        std::unordered_map<std::string, u32> m_SpriteSheetStrToId;
        std::unordered_map<std::string, u32> m_AnimStrToId;
    };
}