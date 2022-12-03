#ifndef _COIN_HPP_
#define _COIN_HPP_

#include "game_object.hpp"
#include "../texture_loader.hpp"

class Coin : public GameObject {
private:
    bool collected;
    float spriteTimer;
    Vector2 currentSpriteIndex;

    void spinCycle() {
        spriteTimer += GetFrameTime();
        if (spriteTimer > 0.1f) {
            spriteTimer = 0;
            currentSpriteIndex.x = currentSpriteIndex.x < 48 ? currentSpriteIndex.x + 16 : 0;
        }
    }
public:
    Coin(Vector2 pos) : GameObject(pos, {16,16}), collected{false}, spriteTimer{0}, currentSpriteIndex{0,0} {};
    ~Coin() = default;

    void SetCollected() {
        collected = true;
    }

    bool IsCollected() {
        return collected;
    }

    virtual void update() override {
        spinCycle();
    }

    virtual void draw(Vector2 offset) const override {
        if (!collected) DrawTextureRec(_coin_tilemap, {currentSpriteIndex.x ,currentSpriteIndex.y, 16, 16}, {rect.x, rect.y}, WHITE);
    }
};

#endif