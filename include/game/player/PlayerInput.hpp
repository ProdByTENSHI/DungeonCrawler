#pragma once

#include "PlayerData.hpp"
#include "PlayerInputController.hpp"
#include "engine/input/InputManager.hpp"
#include "engine/tenshiUtil/eventsystem/EventSystem.h"

namespace tenshi
{
    class PlayerInput : public PlayerInputController
    {
    public:
        PlayerInput();
        ~PlayerInput() override;

        void HandleData(PlayerData& data) override;

    private:
        EventHandler<KeyEvent> OnKeyDown;
        EventHandler<KeyEvent> OnKeyUp;

        PlayerData m_Data;
    };
}
