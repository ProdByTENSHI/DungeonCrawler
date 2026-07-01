#pragma once

#include <random>

class Random {
public:
    //! Returns a Random Int between minInclusive and maxInclusive
    inline static int GetInt(int minInclusive, int maxInclusive) {
        std::random_device _device;
        std::mt19937 rng(_device());
        std::uniform_int_distribution<std::mt19937::result_type> dist(minInclusive, maxInclusive);

        return dist(rng);
    }

    inline static int GetFloat(float minInclusive, float maxInclusive) {
        return minInclusive + static_cast<float>(rand()) / (static_cast<float>(
                   RAND_MAX / (maxInclusive - minInclusive)));
    }
};
