#ifndef _STATE_HPP_
#define _STATE_HPP_

#include "raylib.h"

class State {
protected:
    Vector2 position;    
public:
    State() : position{0,0} {};
    State(Vector2 pos) : position{pos} {};
    ~State() = default;

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