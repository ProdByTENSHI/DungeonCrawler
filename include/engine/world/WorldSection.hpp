#pragma once

#include "engine/tenshiUtil/Types.hpp"
#include "engine/world/WorldSectionData.hpp"
#include "engine/world/NSWE.hpp"

namespace tenshi
{
    // The World is parted into sections to reduce loading the whole world into memory
    // Each Section has an unique identifier, a Name and a NSWE Orientation
    struct WorldSection
    {
        u16 m_Id = 0;

        // From the World Center
        NSWE m_NSWE = NSWE::CENTER;

        // X and Y Index of the Section
        // X, Y = 0 = TOP LEFT of the World
        u8 m_X = 0;
        u8 m_Y = 0;

        // Pointer to the World Section Data
        WorldSectionData* m_Data = nullptr;

        // Holds the N, S, W, E Neighbouring Sections
        // 0 -> N, 1 -> S, 2 -> W, 3 -> E
        // Used for caching neighbouring sections for faster loading times
        u8 m_NeighbourSections[4];

        std::string m_Name = "World Section";
        std::string m_Description = "World Section Description";

        bool operator!=(const WorldSection& rhs) const
        {
            return m_Id != rhs.m_Id;
        }
    };
}