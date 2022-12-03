#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

#include "game_object.hpp"

class Block : public GameObject {
private:
public:
    Block(Vector2 pos, Vector2 size) : GameObject(pos, size) {};
    ~Block() = default;

    virtual void update() override {

    }

    virtual void draw(Vector2 offset) const override {
        
    }
};

#endif