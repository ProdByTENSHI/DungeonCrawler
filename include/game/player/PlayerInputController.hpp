#pragma once
#include "PlayerData.hpp"

namespace tenshi
{
    class PlayerInputController
    {
    public:
        PlayerInputController() {}
        virtual ~PlayerInputController() {}

        virtual void HandleData(PlayerData& data) = 0;
    };
}
