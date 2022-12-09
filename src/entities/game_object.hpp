#ifndef _GAME_OBJECT_HPP_
#define _GAME_OBJECT_HPP_

#include "raylib.h"

class GameObject {
protected:
    Rectangle rect;
public:
    GameObject() : rect{0,0,0,0} {};
    GameObject(Vector2 position) : rect{position.x, position.y, 0, 0} {};
    GameObject(Vector2 position, Vector2 size) : rect{position.x, position.y, size.x, size.y} {};
    ~GameObject() = default;

    virtual Rectangle GetCollision(const Rectangle& other) const {
        return GetCollisionRec(rect, other);
    }

    Rectangle GetRect() const {
        return rect;
    }

    void SetPosition(const Vector2 pos, const Vector2 offset) {
        rect.x = pos.x + offset.x;
        rect.y = pos.y + offset.y;
    }

    virtual void update() = 0;
    virtual void draw(Vector2 offset) const = 0;
};

#endif