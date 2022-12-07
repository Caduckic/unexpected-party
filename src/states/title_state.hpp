#ifndef _TITLE_STATE_HPP_
#define _TITLE_STATE_HPP_

#include "state.hpp"
#include "raylib.h"

class TitleState : public State {
private:
    
public:
    TitleState(Vector2 pos) : State(pos) {};
    ~TitleState() = default;

    virtual void update() override {

    }

    virtual void render() const override {
        DrawTexture(_title_screen, position.x, position.y, WHITE);
    }
};

#endif