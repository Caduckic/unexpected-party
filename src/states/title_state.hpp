#ifndef _TITLE_STATE_HPP_
#define _TITLE_STATE_HPP_

#include "state.hpp"
#include "raylib.h"
#include "../config.hpp"
#include "../texture_loader.hpp"

class TitleState : public State {
private:
    
public:
    TitleState(Vector2 pos) : State(pos) {};
    ~TitleState() = default;

    virtual void update() override {

    }

    virtual void render() const override {
        DrawTexture(_title_screen, position.x, position.y, WHITE);

        // TODO change font color to match pallete
        DrawTextEx(ROMULUS_FONT, "PLAY GAME", {position.x + 80, position.y + 112}, 16, 2, _COLOR3);
        DrawTextEx(ROMULUS_FONT, "QUIT GAME", {position.x + 80, position.y + 144}, 16, 2, _COLOR3);
    }
};

#endif