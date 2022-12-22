#ifndef _UI_CANVAS_HPP
#define _UI_CANVAS_HPP

#include <map>
#include "game_object.hpp"
#include "ui_button.hpp"

class UICanvas : public GameObject {
private:
    std::map<int, UIButton> buttons;
    int currentButtonID;
    float selectionTimer;
    bool holdingNav;
public:
    UICanvas(Vector2 pos, Vector2 size, std::map<int, UIButton> layout) : GameObject(pos, size), buttons{layout}, currentButtonID{0} {};
    ~UICanvas() = default;

    void NavigateButtons(int direction) {
        selectionTimer += GetFrameTime();
        if (selectionTimer > 0) {
            selectionTimer = -2;
            direction > 0 ? GoDown() : GoUp();
        }
        else if (selectionTimer > -1.5 && selectionTimer < 0) {
            selectionTimer = -3;
            direction > 0 ? GoDown() : GoUp();
        }
        else if (selectionTimer > -2.8 && selectionTimer < -2) {
            selectionTimer = -3;
            direction > 0 ? GoDown() : GoUp();
        }
    }

    void GoUp() {
        currentButtonID = currentButtonID - 1 >= 0 ? currentButtonID - 1 : buttons.size() - 1;
    }

    void GoDown() {
        currentButtonID = currentButtonID + 1 < buttons.size() ? currentButtonID + 1 : 0;
    }

    void update() override {
        bool buttonPressed {false};
        for (auto &button : buttons) {
            button.second.update();
            if (button.second.IsSelected() && button.first != currentButtonID) {
                currentButtonID = button.first;
                break;
            }
        }

        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) selectionTimer = 0;

        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT)) {
            NavigateButtons(1);
        }

        else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_D) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_RIGHT)) {
            NavigateButtons(-1);
        }

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            buttonPressed = true;
        }

        for (auto &button : buttons) {
            if (button.first != currentButtonID) {
                button.second.SetSelected(false);
            } else button.second.SetSelected(true);
        }

        if (buttonPressed) {
            for (auto &button : buttons) {
                if (button.first == currentButtonID) {
                    button.second.Press();
                }
            }
        }
    }

    const std::map<int, UIButton>& GetButtons() const {
        return buttons;
    }

    void draw(Vector2 offset) const override {
        for (auto &button : buttons) {
            button.second.draw({rect.x + offset.x, rect.y + offset.y});
        }
        //DrawRectangleLines(rect.x, rect.y, rect.height, rect.width, BLUE);
    }
};

#endif