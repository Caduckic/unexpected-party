#ifndef _TITLE_STATE_HPP_
#define _TITLE_STATE_HPP_

#include "state.hpp"
#include "raylib.h"
#include "../ui_layouts.hpp"
#include "../texture_loader.hpp"
#include "../entities/ui_canvas.hpp"

class TitleState : public State {
private:
    UICanvas menu;
public:
    TitleState(Vector2 pos) : State(pos), menu{{0,0}, {256, 256}, TITLE_LAYOUT} {};
    ~TitleState() = default;

    const UICanvas& GetCurrentCanvas() const override {
        return menu;
    }

    GameState GetGameState() override {
        return TITLE;
    }

    virtual void update() override {
        menu.update();
    }

    virtual void render() const override {
        DrawTexture(_title_screen, position.x, position.y, WHITE);

        menu.draw(position);
        //DrawTextEx(ROMULUS_FONT, "PLAY GAME", {position.x + 80, position.y + 112}, 16, 2, _COLOR3);
        //DrawTextEx(ROMULUS_FONT, "QUIT GAME", {position.x + 80, position.y + 144}, 16, 2, _COLOR3);
    }
};

#endif