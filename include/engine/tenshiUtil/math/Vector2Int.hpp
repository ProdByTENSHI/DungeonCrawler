#pragma once

#include "engine/tenshiUtil/Types.hpp"

#include <functional>
#include <raylib.h>

struct Vector2Int
{
    i32 x = 0;
    i32 y = 0;

    Vector2Int(i32 val) : x(val), y(val)
    {
    }

    Vector2Int(i32 x, i32 y) : x(x), y(y)
    {
    }

    bool operator ==(const Vector2Int& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }

    bool operator !=(const Vector2Int& rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }

    Vector2Int& operator =(const Vector2Int& rhs) = default;

    operator Vector2() const
    {
        return Vector2((f32)x, (f32)y);
    }
};

template <>
struct std::hash<Vector2Int>
{
    std::size_t operator()(const Vector2Int& coord) const noexcept
    {
        return std::hash<i32>()(coord.x) ^ (std::hash<i32>()(coord.y) << 1);
    }
};
