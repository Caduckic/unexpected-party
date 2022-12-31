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
    bool bounced;
    bool colX;

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
        colX = true;
    }

public:
    Coin(Vector2 pos, CoinMode mode) : EntityObject({pos.x + 2, pos.y}, {12,16}, -1), mode{mode}, collected{false}, spriteTimer{0}, currentSpriteIndex{0,0}, bounced{false}, colX{false} {};
    ~Coin() = default;

    void SetCollected() {
        collected = true;
    }

    bool IsCollected() {
        return collected;
    }

    bool IsBounced() {
        return bounced;
    }

    bool IsColX() {
        return colX;
    }

    void Bounce(float dir) {
        direction = dir;
        bounced = !bounced;
    }

    void SetMode(CoinMode newMode) {
        mode = newMode;
    }

    CoinMode GetMode() const {
        return mode;
    }

    void SetGrounded(bool grounded) override {
        if (isGrounded && !grounded) speed = 0;
        isGrounded = grounded;
    }

    virtual void update() override {
        colX = false;
        spinCycle();
        switch (mode)
        {
        case CoinMode::DEFAULT:
            break;
        case CoinMode::ENEMY:
            if (isGrounded) CalculateInputMovement(600, 600, COIN_MAX_SPEED);
            else CalculateInputMovement(200, 200, COIN_MAX_SPEED * 0.75f);
            ApplyMovement();
            break;
        case CoinMode::SHELL:
            if (bounced) {
                speed = direction * SHELL_COIN_MAX_SPEED;
                CalculateInputMovement(600, 600, SHELL_COIN_MAX_SPEED);
                ApplyMovement();
            }
            break;
        default:
            break;
        }
    }

    virtual void draw(Vector2 offset) const override {
        if (!collected) DrawTextureRec(_coin_tilemap, {currentSpriteIndex.x,currentSpriteIndex.y, 16, 16}, {rect.x + offset.x - 2, rect.y + offset.y}, WHITE);
        //if (mode == CoinMode::SHELL) DrawRectangleLinesEx(rect, 1, BLUE);
    }
};

#endif