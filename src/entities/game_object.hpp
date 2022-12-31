#ifndef _GAME_OBJECT_HPP_
#define _GAME_OBJECT_HPP_

#include "raylib.h"
#include <vector>
#include <iostream>
#include <ctime>

bool ContainsID(int id, std::vector<int> &IDs) {
    bool contains {false};
    for (auto &ID : IDs) {
        if (ID == id) {
            contains = true;
            break;
        }
    }
    return contains;
}

int GetRandomID() {
    static std::vector<int> IDs {};
    int newId = GetRandomValue(0, INT16_MAX);
    while (ContainsID(newId, IDs)) {
        newId = GetRandomValue(0, INT16_MAX);
    }
    IDs.push_back(newId);

    return newId;
}

class GameObject {
protected:
    Rectangle rect;
    int id;
public:
    GameObject() : rect{0,0,0,0}, id{GetRandomID()} {};
    GameObject(Vector2 position) : rect{position.x, position.y, 0, 0}, id{GetRandomID()} {};
    GameObject(Vector2 position, Vector2 size) : rect{position.x, position.y, size.x, size.y}, id{GetRandomID()} {};
    ~GameObject() = default;

    bool operator==(const GameObject& rhs) {
        return (id == rhs.id);
    }

    bool operator!=(const GameObject& rhs) {
        return !(id == rhs.id);
    }

    Rectangle GetCollision(const Rectangle& other) const {
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