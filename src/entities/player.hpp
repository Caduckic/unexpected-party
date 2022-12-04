#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <cmath>
#include <string>
#include "game_object.hpp"
#include "../config.hpp"
#include "../texture_loader.hpp"

class Player : public GameObject {
private:
    Color color;
    Vector2 vel;
    Vector2 currentSpriteIndex;
    float direction;
    float currentDirection;
    float speed;
    float acceleration;
    bool isJump;
    bool isGrounded;
    bool isWalking;
    bool doneLanding;
    float spriteTimer;
    bool bothPressed;

    void walkCycle() {
        spriteTimer += std::abs(direction) * GetFrameTime();
        currentSpriteIndex.y = 0;
        if (spriteTimer > 0.1f) {
            spriteTimer = 0;
            currentSpriteIndex.x = currentSpriteIndex.x + 16 <= 48 ? currentSpriteIndex.x + 16 : 0;
        }
    }

    void idleCycle() {
        spriteTimer += GetFrameTime();
        currentSpriteIndex.y = 16;
        currentSpriteIndex.x = currentSpriteIndex.x > 16 ? 0 : currentSpriteIndex.x;
        if (spriteTimer > 0.3f) {
            spriteTimer = 0;
            currentSpriteIndex.x = currentSpriteIndex.x == 0 ? 16 : 0;
        }
    }

    void jumpFrame() {
        currentSpriteIndex = {32,16};
    }

    void fallFrame() {
        currentSpriteIndex = {0,0};
    }

    void landFrame() {
        spriteTimer += GetFrameTime();
        currentSpriteIndex = {16,16};
        if (spriteTimer > 0.2f) doneLanding = true;
    }

    void deathAnimation() {
        spriteTimer += GetFrameTime();
        if (spriteTimer > -1.8 && spriteTimer < 0) {
            spriteTimer = -2;
            currentSpriteIndex.x = currentSpriteIndex.x == 32 ? 48 : 32;
        }
        else if (spriteTimer > 0 && spriteTimer < 0.4) currentSpriteIndex = {48, 16};
        else if (spriteTimer > 0.4 && spriteTimer < 1) currentSpriteIndex = {32, 32};
        else if (spriteTimer > 1) spriteTimer = -2;
    }
public:
    Player(Vector2 pos, Vector2 size, Color color, float dir) : GameObject(pos, size), color{color}, vel{0, START_GRAVITY}, currentSpriteIndex{0,16},
        direction{0}, currentDirection{dir}, speed{0}, acceleration{PLAYER_ACCELERATION}, isJump{false}, isGrounded{false}, isWalking{false}, doneLanding{true}, spriteTimer{0}, bothPressed{false} {};
    ~Player() = default;

    virtual void input() {
        float newDir {direction};
        float oldDir {direction};
        direction = 0;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            direction += -1;
            if (oldDir + direction == 0 && !bothPressed) {
                bothPressed = true;
                newDir = -1;
            }
        } else bothPressed = false;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            direction += 1;
            if (oldDir + direction == 0 && !bothPressed) {
                bothPressed = true;
                newDir = 1;
            }
        } else bothPressed = false;

        if (bothPressed) direction += newDir;
        //else direction = 0;

        if (direction != 0) currentDirection = direction;

        if (IsKeyPressed(KEY_SPACE) && isGrounded) {
            isJump = true;
            doneLanding = true;
        }
    }

    virtual void update() override {
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

        vel.y = std::min(vel.y + (START_GRAVITY * GetFrameTime()), MAX_GRAVITY);
        vel.x = speed;
        if (isJump) {
            isJump = false;
            isGrounded = false;
            vel.y = PLAYER_JUMP;
        }

        rect.x += vel.x * GetFrameTime();
        rect.y += vel.y * GetFrameTime() < 16 ? vel.y * GetFrameTime() : 15;

        if (vel.y < 0) jumpFrame();
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
                }
                else if (col.y >= other.y) {
                    rect.y = other.y - rect.height;
                    if (!isGrounded && oldVel > 250) {
                        spriteTimer = 0;
                        doneLanding = false;
                        speed = 0;
                    }
                    isGrounded = true;
                } 
        }
        else if ((col.height >= rect.height || col.height >= other.height || col.height >= rect.y + rect.width - other.y || col.height >= other.y + other.height - rect.y) && (position.x >= other.x + other.width || position.x + rect.width <= other.x)) {
            if (col.x + col.width >= other.x + other.width) {
                rect.x = other.x + other.width;
            }
            else if (col.x <= other.x) {
                rect.x = other.x - rect.width;
            }
        }
        else rect.y = other.y - rect.height; // dirty fix
    }

    void setGrounded(bool grounded) {
        isGrounded = grounded;
    }

    virtual void draw(const Vector2 offset) const override {
        int facingDir = (currentDirection > 0) ? 1 : -1;
        DrawTextureRec(_player1_tilemap, {currentSpriteIndex.x, currentSpriteIndex.y, 16.f * facingDir,16}, {std::round(rect.x - 2 + offset.x), std::round(rect.y + offset.y)}, WHITE);
    }
};

#endif