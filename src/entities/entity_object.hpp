#ifndef _ENTITY_OBJECT_HPP_
#define _ENTITY_OBJECT_HPP_

#include <cmath>
#include "game_object.hpp"
#include "../config.hpp"

class EntityObject : public GameObject {
protected:
    Vector2 vel;
    Vector2 currentSpriteIndex;
    float direction;
    float currentDirection;
    float speed;
    bool isGrounded;
    bool isWalking;

    virtual void CalculateInputMovement(float accelRate, float deaccelRate, float maxSpeed) {
        if (direction != 0) {
            isWalking = true;
            speed += direction * accelRate * GetFrameTime();
            if (speed > maxSpeed) speed = maxSpeed;
            if (speed < -maxSpeed) speed = -maxSpeed;
        }
        else if (isGrounded) {
            if (speed > 0) {
                speed-= deaccelRate * GetFrameTime();
                speed < 0 ? speed = 0 : speed = speed;
            }
            if (speed < 0) {
                speed += deaccelRate * GetFrameTime();
                speed > 0 ? speed = 0 : speed = speed;
            }
        }
        else {
            if (speed > 0) {
                speed-= (deaccelRate / 3) * GetFrameTime();
                speed < 0 ? speed = 0 : speed = speed;
            }
            if (speed < 0) {
                speed += (deaccelRate / 3) * GetFrameTime();
                speed > 0 ? speed = 0 : speed = speed;
            }
        }
    }

    virtual void ApplyMovement() {
        vel.x = speed;
        vel.y = std::min(vel.y + (START_GRAVITY * GetFrameTime()), MAX_GRAVITY);

        // rect.y needs to be clamped to 15, object will go through collisions at low fps if not
        rect.x += vel.x * GetFrameTime();
        rect.y += vel.y * GetFrameTime() < 16 ? vel.y * GetFrameTime() : 15;
    }
    
    virtual void CorrectCollisionActionY() {

    }

    virtual void CorrectCollisionActionX() {

    }

    virtual void CorrectionCollisionLand() {

    }

    virtual void CorrectionCollisionGrounded() {

    }
public:
    EntityObject(Vector2 pos, Vector2 size, float dir) : GameObject(pos, size), vel{0, START_GRAVITY}, currentSpriteIndex{0,0}, direction{dir}, currentDirection{dir}, speed{0}, isGrounded{false}, isWalking{false} {};
    ~EntityObject() = default;

    Vector2 GetVelocity() {
        return vel;
    }

    void SetGrounded(bool grounded) {
        isGrounded = grounded;
    }

    bool IsGrounded() {
        return isGrounded;
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
                    CorrectCollisionActionY();
                }
                else if (col.y >= other.y) {
                    rect.y = other.y - rect.height;
                    CorrectCollisionActionY();
                    if (!isGrounded && oldVel > 250) {
                        CorrectionCollisionLand();
                        speed = 0;
                    }
                    isGrounded = true;
                    CorrectionCollisionGrounded();
                }
        }
        else if ((col.height >= rect.height || col.height >= other.height || col.height >= rect.y + rect.width - other.y || col.height >= other.y + other.height - rect.y) && (position.x >= other.x + other.width || position.x + rect.width <= other.x)) {
            if (col.x + col.width >= other.x + other.width) {
                rect.x = other.x + other.width;
                CorrectCollisionActionX();
            }
            else if (col.x <= other.x) {
                rect.x = other.x - rect.width;
                CorrectCollisionActionX();
            }
        }
        else { // dirty fix
            rect.y = other.y - rect.height;
            CorrectCollisionActionY();
        }
    }

    virtual void input() {
        if (IsKeyDown(KEY_M)) direction = 1;
        else direction = 0;
    }

    virtual void update() override {
        CalculateInputMovement(600, 600, PLAYER_MAX_SPEED);
        ApplyMovement();

        // must always end with this
        isWalking = false;
    }

    virtual void draw(Vector2 offset) const override {
        DrawRectangle(rect.x + offset.x, rect.y + offset.y, rect.width, rect.height, PURPLE);
    }
};

#endif