#ifndef _COIN_HPP_
#define _COIN_HPP_

#include "entity_object.hpp"
#include "player.hpp"
#include "../texture_loader.hpp"

enum class CoinMode {UNKNOWN = -1, DEFAULT = 0, ENEMY, SHELL};

class Coin : public EntityObject {
private:
    CoinMode mode;
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

    virtual void CorrectCollisionActionY() {

    }

    virtual void CorrectCollisionActionX() {
        direction = -direction;
        speed = -speed;
    }

public:
    Coin(Vector2 pos, CoinMode mode) : EntityObject(pos, {16,16}, -1), mode{mode}, collected{false}, spriteTimer{0}, currentSpriteIndex{0,0} {};
    ~Coin() = default;

    void SetCollected() {
        collected = true;
    }

    bool IsCollected() {
        return collected;
    }

    void SetMode(CoinMode newMode) {
        mode = newMode;
    }

    CoinMode GetMode() const {
        return mode;
    }

    virtual void update() override {
        spinCycle();
        switch (mode)
        {
        case CoinMode::DEFAULT:
            break;
        case CoinMode::ENEMY:
            CalculateInputMovement(600, 600, COIN_MAX_SPEED);
            ApplyMovement();
            break;
        case CoinMode::SHELL:
            break;
        default:
            break;
        }
    }

    virtual void draw(Vector2 offset) const override {
        if (!collected) DrawTextureRec(_coin_tilemap, {currentSpriteIndex.x,currentSpriteIndex.y, 16, 16}, {rect.x + offset.x, rect.y + offset.y}, WHITE);
    }
};

#endif