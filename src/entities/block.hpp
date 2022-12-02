#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

#include "game_object.hpp"

class Block : public GameObject {
private:
    Color color;
public:
    Block(Vector2 pos, Vector2 size, Color col) : GameObject(pos, size), color{col} {};
    ~Block() = default;

    virtual void update() override {

    }

    virtual void draw(Vector2 offset) const override {
        DrawRectangle(rect.x + offset.x, rect.y + offset.y, rect.width, rect.height, color);
    }
};

#endif