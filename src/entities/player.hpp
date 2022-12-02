#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <cmath>
#include "game_object.hpp"
#include "../config.hpp"

class Player : public GameObject {
private:
    Color color;
    Vector2 vel;
    float direction;
    float speed;
    float acceleration;
    bool isJump;
    bool isGrounded;
public:
    Player(Vector2 pos, Vector2 size, Color color) : GameObject(pos, size), color{color}, vel{0, START_GRAVITY}, direction{0}, speed{0}, acceleration{PLAYER_ACCELERATION}, isJump{false}, isGrounded{false} {};
    ~Player() = default;

    virtual void input() {
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            direction = -1;
        }
        else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            direction = 1;
        }
        else direction = 0;

        if (IsKeyPressed(KEY_SPACE) && isGrounded) {
            isJump = true;
        }
    }

    virtual void update() override {
        if (direction != 0) {
            speed += direction * 600 * GetFrameTime();
            if (speed > PLAYER_MAX_SPEED) speed = PLAYER_MAX_SPEED;
            if (speed < -PLAYER_MAX_SPEED) speed = -PLAYER_MAX_SPEED;
        }
        else if (isGrounded) {
            if (speed > 0) speed -= 600 * GetFrameTime();
            if (speed < 0) speed += 600 * GetFrameTime();
        }
        else {
            if (speed > 0) speed -= 100 * GetFrameTime();
            if (speed < 0) speed += 100 * GetFrameTime();
        }

        vel.y = std::min(vel.y + (START_GRAVITY * GetFrameTime()), MAX_GRAVITY);
        vel.x = speed;
        if (isJump) {
            isJump = false;
            isGrounded = false;
            vel.y = PLAYER_JUMP;
        }

        rect.x += vel.x * GetFrameTime();
        rect.y += vel.y * GetFrameTime();
    }

    void CorrectCollision(const Rectangle& other, const Rectangle& col) {
        Vector2 position = {rect.x - vel.x * GetFrameTime(), rect.y - vel.y * GetFrameTime()};
        if (col.width >= rect.width && position.y + rect.height <= other.y || col.width >= other.width && position.y + rect.height <= other.y ||
            col.width >= rect.x + rect.width - other.x && position.y + rect.height <= other.y || col.width >= other.x + other.width - rect.x && position.y + rect.height <= other.y ||
            col.width >= rect.width && position.y >= other.y + other.height || col.width >= other.width && position.y >= other.y + other.height ||
            col.width >= rect.x + rect.width - other.x && position.y >= other.y + other.height || col.width >= other.x + other.width - rect.x && position.y >= other.y + other.height) {
                vel.y = 0;
                if (col.y + col.height >= other.y + other.height) {
                    rect.y = other.y + other.height;
                }
                else if (col.y >= other.y) {
                    rect.y = other.y - rect.height;
                    isGrounded = true;
                }
        }
        else if (col.height >= rect.height || col.height >= other.height || col.height >= rect.y + rect.width - other.y || col.height >= other.y + other.height - rect.y && position.x + rect.width <= other.x || position.x >= other.x + other.width) {
            if (col.x + col.width >= other.x + other.width) {
                rect.x = other.x + other.width;
            }
            if (col.x >= other.x) {
                rect.x = other.x - rect.width;
            }
        }
    }

    void setGrounded(bool grounded) {
        isGrounded = grounded;
    }

    virtual void draw(const Vector2 offset) const override {
        DrawRectangle(rect.x + offset.x, rect.y + offset.y, rect.width, rect.height, color);
    }
};

#endif