#ifndef _NEW_PLAYER_HPP_
#define _NEW_PLAYER_HPP_

#include "entity_object.hpp"
#include "../texture_loader.hpp"

class Player : public EntityObject {
private:
    Rectangle headHitBox;
    int playerNum;
    float acceleration;
    bool isJump;
    bool doneLanding;
    float spriteTimer;
    bool bothPressed;
    bool isTakingDamage;
    float damageDir;

    void walkCycle() {
        headHitBox.y = rect.y;
        spriteTimer += std::abs(direction) * GetFrameTime();
        currentSpriteIndex.y = 0;
        if (spriteTimer > 0.1f) {
            spriteTimer = 0;
            currentSpriteIndex.x = currentSpriteIndex.x + 16 <= 48 ? currentSpriteIndex.x + 16 : 0;
        }

        if (currentSpriteIndex.x == 16) {
            headHitBox.y = rect.y - 1;
        }
        else headHitBox.y = rect.y;
    }

    void idleCycle() {
        spriteTimer += GetFrameTime();
        currentSpriteIndex.y = 16;
        currentSpriteIndex.x = currentSpriteIndex.x > 16 ? 0 : currentSpriteIndex.x;
        if (spriteTimer > 0.3f) {
            spriteTimer = 0;
            currentSpriteIndex.x = currentSpriteIndex.x == 0 ? 16 : 0;
            if (currentSpriteIndex.x == 16) {
                headHitBox.y = rect.y + 1;
            }
            else {
                headHitBox.y = rect.y;
            }
        }
    }

    void jumpFrame() {
        headHitBox.y = rect.y;
        currentSpriteIndex = {32,16};
    }

    void fallFrame() {
        headHitBox.y = rect.y;
        currentSpriteIndex = {0,0};
    }

    void landFrame() {
        headHitBox.y = rect.y + 1;
        spriteTimer += GetFrameTime();
        currentSpriteIndex = {16,16};
        if (spriteTimer > 0.2f) doneLanding = true;
    }

    void deathAnimation() {
        headHitBox.y = rect.y;
        spriteTimer += GetFrameTime();
        if (spriteTimer > -1.8 && spriteTimer < 0) {
            spriteTimer = -2;
            currentSpriteIndex.x = currentSpriteIndex.x == 32 ? 48 : 32;
        }
        else if (spriteTimer > 0 && spriteTimer < 0.4) currentSpriteIndex = {48, 16};
        else if (spriteTimer > 0.4 && spriteTimer < 1) currentSpriteIndex = {32, 32};
        else if (spriteTimer > 1) spriteTimer = -2;
    }

    void takeDamageCycle() {
        if (currentSpriteIndex.x != 0 && currentSpriteIndex.x != 16) currentSpriteIndex.x = 0;
        currentSpriteIndex.y = 32;
        headHitBox.y = rect.y + 1;
        spriteTimer += GetFrameTime();
        if (spriteTimer > 0.15) {
            spriteTimer = 0;
            currentSpriteIndex.x = currentSpriteIndex.x == 16 ? 0 : 16;
        }
    }

    virtual void CorrectCollisionActionX() {
        headHitBox.x = rect.x;
        speed = 0;
    }

    virtual void CorrectCollisionActionY() {
        headHitBox.y = rect.y;
    }

    virtual void CorrectionCollisionLand() {
        spriteTimer = 0;
        doneLanding = false;
    }

    virtual void CorrectionCollisionGrounded() {
        isTakingDamage = false;
    }
public:
    Player(Vector2 pos, Vector2 size, float dir) : EntityObject(pos, size, dir), headHitBox{pos.x,pos.y, size.x, 4}, playerNum{dir > 0 ? 1 : 2}, acceleration{PLAYER_ACCELERATION}, isJump{false}, doneLanding{true}, spriteTimer{0}, bothPressed{false}, isTakingDamage{false}, damageDir{0} {};
    ~Player() = default;

    void CalculateDamageMovement() {
        speed -= -currentDirection * 180 * GetFrameTime();
        if ((-currentDirection > 0 && speed < 0) || (-currentDirection < 0 && speed > 0)) {
            speed = 0;
        }
    }

    bool CalcHeadBounce(const Rectangle& other, const Vector2& velocity) {
        Vector2 position = {rect.x - vel.x * GetFrameTime(), rect.y - vel.y * GetFrameTime()};
        Vector2 otherOldPos = {other.x - velocity.x * GetFrameTime(), other.y - velocity.y * GetFrameTime()};
        if (position.y + rect.height < otherOldPos.y && (vel.y != velocity.y || velocity.y == 0)) {//std::abs(vel.y - velocity.y) > 0) {
            rect.y = other.y - rect.height;
            headHitBox.y = rect.y;
            vel.y = (velocity.y * GetFrameTime()) + PLAYER_BOUNCE + (vel.y * GetFrameTime());//(velocity.y * GetFrameTime()) + PLAYER_BOUNCE;
            return true;
        }
        return false;
    }

    virtual void input() override {
        float newDir {direction};
        float oldDir {direction};

        KeyboardKey UP, LEFT, RIGHT;

        switch (playerNum)
        {
        case 1:
            UP = KEY_W;
            LEFT = KEY_A;
            RIGHT = KEY_D;
            break;
        case 2:
            UP = KEY_UP;
            LEFT = KEY_LEFT;
            RIGHT = KEY_RIGHT;
        default:
            UP = KEY_UP;
            LEFT = KEY_LEFT;
            RIGHT = KEY_RIGHT;
            break;
        }

        direction = 0;
        if (!isTakingDamage) {
            if (IsKeyDown(LEFT)) {
                direction += -1;
                if (oldDir + direction == 0 && !bothPressed) {
                    bothPressed = true;
                    newDir = -1;
                }
            } else bothPressed = false;
            if (IsKeyDown(RIGHT)) {
                direction += 1;
                if (oldDir + direction == 0 && !bothPressed) {
                    bothPressed = true;
                    newDir = 1;
                }
            } else bothPressed = false;

            if (bothPressed) direction += newDir;
            //else direction = 0;

            if (direction != 0) currentDirection = direction;

            if (IsKeyPressed(UP) && isGrounded) {
                isJump = true;
                doneLanding = true;
            }
        }
    }

    bool IsTakingDamage() {
        damageDir = -currentDirection;
        return isTakingDamage;
    }

    Rectangle GetHeadHitBox() {
        return headHitBox;
    }

    void TakeDamage() {
        isTakingDamage = true;

        vel.y = -100;
        speed = -currentDirection * 100;
    }

    virtual void update() override {
        if (!isTakingDamage) {
            CalculateInputMovement(600, 600, PLAYER_MAX_SPEED);
        } else {
            CalculateDamageMovement();
        }

        if (isJump) {
            isJump = false;
            isGrounded = false;
            vel.y = PLAYER_JUMP;
        }

        ApplyMovement();
        headHitBox.x = rect.x;

        if (isTakingDamage) takeDamageCycle(); 
        else if (vel.y < 0) jumpFrame();
        else if (!isGrounded) fallFrame();
        else if (!doneLanding) landFrame();
        else if (isWalking) walkCycle();
        else if (!isWalking) idleCycle();
        //deathAnimation();

        isWalking = false;
    }

    virtual void draw(Vector2 offset) const override {
        int facingDir = (currentDirection > 0) ? 1 : -1;
        DrawTextureRec(playerNum == 1 ? _player1_tilemap : _player2_tilemap, {currentSpriteIndex.x, currentSpriteIndex.y, 16.f * facingDir,16}, {std::round(rect.x - 2 + offset.x), std::round(rect.y + offset.y)}, WHITE);
        //DrawRectangleLinesEx(rect, 1, BLUE);
        /*if (playerNum == 2) {
            DrawText(std::to_string(vel.y).c_str(),0,0,30,BLUE);
        }*/
    }
};

#endif