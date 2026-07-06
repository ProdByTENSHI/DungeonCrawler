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

        Event<> OnShootEvent;
        Event<> OnReloadEvent;

    private:
        EventHandler<KeyEvent> OnKeyDown;
        EventHandler<KeyEvent> OnKeyUp;
        EventHandler<MouseEvent> OnMouseDown;
        EventHandler<MouseEvent> OnMouseUp;

        PlayerData m_Data;
    };
}
