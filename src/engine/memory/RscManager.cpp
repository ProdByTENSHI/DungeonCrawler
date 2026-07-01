#include "engine/memory/RscManager.hpp"
#include "engine/globals/Constants.hpp"

#include <fstream>

namespace tenshi
{
    RscManager::RscManager()
    {
    }

    void RscManager::LoadAssets()
    {
        // -- Load File
        std::ifstream file(ASSETS_MANIFEST_PATH);
        if (!file.is_open())
            throw std::runtime_error("Could not open Asset Manifest!");

        json j;
        file >> j;

        std::unordered_map<std::string, Texture2D*> m_TextureCache;

        // -- Iterate Json File
        for (const auto& tex : j["textures"])
        {
            std::string _id = GetValue<std::string>(tex, "id");
            std::string _path = GetValue<std::string>(tex, "path");

            u32 _internalId = LoadTex(_id, _path);
            m_TexStrToId.insert({_id, _internalId});

            spdlog::info("Loaded Texture: {} : {}", _id, _internalId);
        }

        PopulateAssetBindings(RscType::Texture);

        for (const auto& ssheet : j["sprite_sheets"])
        {
            std::string _id = GetValue<std::string>(ssheet, "id");
            u32 _textureId = m_TexStrToId[GetValue<std::string>(ssheet, "texture")];
            u32 _fWidth = GetValue<u32>(ssheet, "frame_width");
            u32 _fHeight = GetValue<u32>(ssheet, "frame_height");

            u32 _internalId = LoadSpriteSheet(_id, _textureId, _fWidth, _fHeight);
            m_SpriteSheetStrToId.insert({_id, _internalId});
        }
        PopulateAssetBindings(RscType::SpriteSheet);

        // Implement Sprites here

        for (const auto& anim : j["animations"])
        {
            std::string _id = GetValue<std::string>(anim, "id");
            std::string _ssheet = GetValue<std::string>(anim, "sprite_sheet");
            f32 _interval = GetValue<f32>(anim, "interval");

            u32 _ssheetId = m_SpriteSheetStrToId[_ssheet];
            SpriteSheet* spriteSheet = GetSpritesheet(_ssheetId);

            f32 _fWidth = (f32)spriteSheet->GetFrameWidth();
            f32 _fHeight = (f32)spriteSheet->GetFrameHeight();

            std::vector<Rectangle> _frames;
            i32 _it = 0;
            for (const auto& frame : anim["frames"])
            {
                if (!frame.is_array() || frame.size() != 2)
                {
                    throw std::runtime_error(std::string("Frame does not match Animation Format: ") +
                        _id);
                }

                _frames.push_back({(f32)frame[0], (f32)frame[1], _fWidth, _fHeight});
                ++_it;
            }

            u32 _internalId = LoadAnimation(_id, _ssheetId, _interval, _frames);
            m_AnimStrToId.insert({_id, _internalId});
        }

        // -- Populate Constant Asset IDs
        PopulateAssetBindings(RscType::Animation);
    }

    Texture2D* RscManager::GetTexture(u32 id)
    {
        if (id > m_TextureCache.size() - 1)
            return nullptr;

        return m_TextureCache[id];
    }

    SpriteSheet* RscManager::GetSpritesheet(u32 id)
    {
        if (id > m_SpriteSheetCache.size() - 1)
            return nullptr;

        return m_SpriteSheetCache[id];
    }

    Animation* RscManager::GetAnimation(u32 id)
    {
        if (id > m_AnimCache.size())
            throw std::runtime_error(std::string("Animation ID is out of Bounds: ")
                + std::to_string(id));

        return m_AnimCache[id];
    }

    u32 RscManager::LoadTex(const std::string& id, const std::string& path)
    {
        // Load Texture
        u32 _id = m_TextureCache.size();

        Texture2D* texture = new Texture2D();
        *texture = LoadTexture(path.c_str());

        m_TextureCache.push_back(texture);

        return _id;
    }

    u32 RscManager::LoadSpriteSheet(const std::string& id, u32 textureId, u32 fWidth, u32 fHeight)
    {
        u32 _id = m_SpriteSheetCache.size();

        SpriteSheet* spriteSheet = new SpriteSheet(_id, textureId, fWidth, fHeight);;
        m_SpriteSheetCache.push_back(spriteSheet);

        spdlog::info("Loading Sprite Sheet {} : {} with Texture {}", id, _id, textureId);

        return _id;
    }

    u32 RscManager::LoadAnimation(const std::string& id, u32 ssheetId,
                                  f32 interval, std::vector<Rectangle> frames)
    {
        u32 _id = m_AnimCache.size();

        Animation* anim = new Animation(ssheetId, interval, frames);
        m_AnimCache.push_back(anim);

        spdlog::info("Loading Animation: {} : {} with Sprite Sheet {}", id, _id,
                     ssheetId);

        return _id;
    }

    void RscManager::PopulateAssetBindings(RscType type)
    {
        switch (type)
        {
        case RscType::Texture:
            for (auto& b : Textures::textureBinding)
            {
                auto it = m_TexStrToId.find(b.m_Name);
                if (it == m_TexStrToId.end())
                    throw std::runtime_error(std::string("Missing Texture: : ") + b.m_Name);

                *b.m_Target = it->second;
            }
            break;

        case RscType::SpriteSheet:
            for (auto& b : SpriteSheets::spriteSheetBinding)
            {
                auto it = m_SpriteSheetStrToId.find(b.m_Name);
                if (it == m_SpriteSheetStrToId.end())
                    throw std::runtime_error(std::string("Missing Sprite Sheet: ") + b.m_Name);

                *b.m_Target = it->second;
            }
            break;

        case RscType::Animation:
            for (auto& b : Animations::animBinding)
            {
                auto it = m_AnimStrToId.find(b.m_Name);
                if (it == m_AnimStrToId.end())
                    throw std::runtime_error(std::string("Missing Animation: ") + b.m_Name);

                *b.m_Target = it->second;
            }
            break;

        default:
            spdlog::info("Populate Asset Binding Type {} not Implemented", (u32)type);
            break;
        }
    }
}