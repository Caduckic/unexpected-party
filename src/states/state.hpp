#ifndef _STATE_HPP_
#define _STATE_HPP_

#include "raylib.h"
#include "../entities/ui_canvas.hpp"

enum GameState {UNKNOWN = -1, TITLE = 0, OPTIONS, PLAY, ENDING};

class State {
protected:
    Vector2 position;    
public:
    State() : position{0,0} {};
    State(Vector2 pos) : position{pos} {};
    ~State() = default;

    virtual GameState GetGameState() = 0;
    virtual const UICanvas& GetCurrentCanvas() const = 0;

    virtual int GetLevelNum() {
        return -1;
    }

    Vector2 getPosition() const {
        return position;
    }

    void setPosition(const Vector2 pos) {
        position = pos;
    }

    virtual void init() {};
    virtual void update() = 0;
    virtual void render() const = 0;
};

#endif