#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <cmath>
#include <iostream>
#include <string>
#include "game_object.hpp"
#include "../config.hpp"
#include "../texture_loader.hpp"

class Player : public GameObject {
private:
    Color color;
    Vector2 vel;
    Vector2 currentSpriteIndex;
    Rectangle headHitBox;
    float direction;
    float currentDirection;
    int playerNum;
    float speed;
    float acceleration;
    bool isJump;
    bool isGrounded;
    bool isWalking;
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
public:
    Player(Vector2 pos, Vector2 size, Color color, float dir) : GameObject(pos, size), color{color}, vel{0, START_GRAVITY}, currentSpriteIndex{0,16}, headHitBox{pos.x,pos.y, size.x, 4},
        direction{0}, currentDirection{dir}, playerNum{dir > 0 ? 1 : 2}, speed{0}, acceleration{PLAYER_ACCELERATION}, isJump{false}, isGrounded{false}, isWalking{false}, doneLanding{true}, spriteTimer{0}, bothPressed{false} {};
    ~Player() = default;

    virtual void input() {
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

    virtual void update() override {
        if (!isTakingDamage){
            if (direction != 0) {
                isWalking = true;
                speed += direction * 600 * GetFrameTime();
                if (speed > PLAYER_MAX_SPEED) speed = PLAYER_MAX_SPEED;
                if (speed < -PLAYER_MAX_SPEED) speed = -PLAYER_MAX_SPEED;
            }
            else if (isGrounded) {
                if (speed > 0) {
                    speed -= 600 * GetFrameTime();
                    speed < 0 ? speed = 0 : speed = speed;
                }
                if (speed < 0) {
                    speed += 600 * GetFrameTime();
                    speed > 0 ? speed = 0 : speed = speed;
                }
            }
            else {
                if (speed > 0) {
                    speed -= 200 * GetFrameTime();
                    speed < 0 ? speed = 0 : speed = speed;
                }
                if (speed < 0) {
                    speed += 200 * GetFrameTime();
                    speed > 0 ? speed = 0 : speed = speed;
                }
            }
        } else {
            speed -= -currentDirection * 180 * GetFrameTime();
            if ((-currentDirection > 0 && speed < 0) || (-currentDirection < 0 && speed > 0)) {
                speed = 0;
            }
            
        }

        vel.y = std::min(vel.y + (START_GRAVITY * GetFrameTime()), MAX_GRAVITY);
        vel.x = speed;
        if (isJump) {
            isJump = false;
            isGrounded = false;
            vel.y = PLAYER_JUMP;
        }

        rect.x += vel.x * GetFrameTime();
        rect.y += vel.y * GetFrameTime() < 16 ? vel.y * GetFrameTime() : 15;
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

    void CorrectCollision(const Rectangle& other, const Rectangle& col) {
        Vector2 position = {rect.x - vel.x * GetFrameTime(), rect.y - vel.y * GetFrameTime()};
        if ((col.width >= rect.width && position.y + rect.height <= other.y) || (col.width >= other.width && position.y + rect.height <= other.y) ||
            (col.width >= rect.x + rect.width - other.x && position.y + rect.height <= other.y) || (col.width >= std::abs(other.x + other.width - rect.x) && position.y + rect.height <= other.y) ||
            (col.width >= rect.width && position.y >= other.y + other.height) || (col.width >= other.width && position.y >= other.y + other.height) ||
            (col.width >= rect.x + rect.width - other.x && position.y >= other.y + other.height) || (col.width >= std::abs(other.x + other.width - rect.x) && position.y >= other.y + other.height)) {
                float oldVel = vel.y;
                vel.y = 0;
                if (col.y + col.height >= other.y + other.height) {
                    rect.y = other.y + other.height;
                    headHitBox.y = rect.y;
                }
                else if (col.y >= other.y) {
                    rect.y = other.y - rect.height;
                    headHitBox.y -= position.y - rect.y;
                    if (!isGrounded && oldVel > 250) {
                        spriteTimer = 0;
                        doneLanding = false;
                        speed = 0;
                    }
                    isGrounded = true;
                    isTakingDamage = false;
                } 
        }
        else if ((col.height >= rect.height || col.height >= other.height || col.height >= rect.y + rect.width - other.y || col.height >= other.y + other.height - rect.y) && (position.x >= other.x + other.width || position.x + rect.width <= other.x)) {
            if (col.x + col.width >= other.x + other.width) {
                rect.x = other.x + other.width;
                headHitBox.x = rect.x;
            }
            else if (col.x <= other.x) {
                rect.x = other.x - rect.width;
                headHitBox.x = rect.x;
            }
        }
        else { // dirty fix
            rect.y = other.y - rect.height;
            headHitBox.y = rect.y;
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

    bool IsTakingDamage() {
        damageDir = -currentDirection;
        return isTakingDamage;
    }

    void TakeDamage() {
        isTakingDamage = true;

        vel.y = -100;
        speed = -currentDirection * 100;
    }

    Vector2 GetVelocity() {
        return vel;
    }

    Rectangle GetHeadHitBox() {
        return headHitBox;
    }

    void setGrounded(bool grounded) {
        isGrounded = grounded;
    }

    virtual void draw(const Vector2 offset) const override {
        int facingDir = (currentDirection > 0) ? 1 : -1;
        DrawTextureRec(playerNum == 1 ? _player1_tilemap : _player2_tilemap, {currentSpriteIndex.x, currentSpriteIndex.y, 16.f * facingDir,16}, {std::round(rect.x - 2 + offset.x), std::round(rect.y + offset.y)}, WHITE);
        //DrawRectangleLinesEx(headHitBox, 1, BLUE);
        if (playerNum == 2) {
            //DrawText(std::to_string(vel.y).c_str(),0,0,30,BLUE);
        }
    }
};

#endif