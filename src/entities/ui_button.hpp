#ifndef _UI_BUTTON_HPP_
#define _UI_BUTTON_HPP_

#include <string>
#include "game_object.hpp"

// i dont wanna deal with lambda's in the C++ this time lol
enum class UIAction {UNKNOWN = -1, GOTO_PLAY = 0, QUIT_GAME, GOTO_TITLE};

class UIButton : public GameObject {
private:
    std::string text;
    UIAction action;
    bool isSelected;
public:
    UIButton(Vector2 pos, Vector2 size, UIAction action) : GameObject(pos, size), action{action} {};
    ~UIButton();

    bool IsSelected() {
        return isSelected;
    }

    void SetSelected(bool s) {
        isSelected = s;
    }

    void update() override {

    }

    void draw(Vector2 offset) const override {
        
    }
};

#endif