#ifndef _UI_BUTTON_HPP_
#define _UI_BUTTON_HPP_

#include <string>
#include <cmath>
#include "../config.hpp"
#include "game_object.hpp"
#include "texture_loader.hpp"
#include "../camera_manager.hpp"
//#include "../states/state_manager.hpp"

// i dont wanna deal with passing lambda's in the C++ this time lol
enum class UIAction {UNKNOWN = -1, GOTO_PLAY = 0, QUIT_GAME, GOTO_TITLE};

class UIButton : public GameObject {
private:
    std::string text;
    UIAction action;
    bool isSelected;
    bool isPressed;
public:
    UIButton(Vector2 pos, Vector2 size, std::string text, UIAction action) : GameObject(pos, size), text{text}, action{action}, isSelected{false}, isPressed{false} {};
    UIButton(Vector2 pos, Vector2 size, std::string text, UIAction action, bool IsSelected) : GameObject(pos, size), text{text}, action{action}, isSelected{isSelected}, isPressed{false} {};
    ~UIButton() = default;

    bool IsPressed() const {
        return isPressed;
    }

    bool IsSelected() const {
        return isSelected;
    }

    void SetSelected(bool s) {
        isSelected = s;
    }

    bool GetMouseCollison() const {
        return CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), CameraManager::Get().GetCam()), rect);
    }

    UIAction GetAction() const {
        return action;
    }

    void update() override {
        if (GetMouseCollison()) {
            isSelected = true;
        }
        if (GetMouseCollison() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isPressed = true;
        }
    }

    void draw(Vector2 offset) const override {
        Vector2 centreOffset = {(rect.width - (MeasureTextEx(ROMULUS_FONT, text.c_str(), 16, 1).x)) / 2, (rect.height - (MeasureTextEx(ROMULUS_FONT, text.c_str(), 16, 1).y)) / 2};
        DrawRectangle(rect.x + offset.x, rect.y + offset.y, rect.width, rect.height, BLUE);
        DrawTextEx(ROMULUS_FONT, text.c_str(), {rect.x + centreOffset.x + offset.x, rect.y + centreOffset.y + offset.y}, 16, 1, _COLOR3);
        if (isSelected) DrawTexture(_ui_arrow, rect.x + offset.x - 16, rect.y + offset.y, WHITE);
    }
};

#endif