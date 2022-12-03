#ifndef _PLAY_STATE_HPP_
#define _PLAY_STATE_HPP_

#include <vector>
#include "state.hpp"
#include "../entities/player.hpp"
#include "../entities/block.hpp"
#include "../texture_loader.hpp"
#include "../resources/levels/level1_data.hpp"

class PlayState : public State {
private:
    Player player;
    std::vector<Block> walls;
public:
    PlayState(Vector2 pos) : State(pos), player{{100,100}, {12,16}, RED, 1}, walls{level1_walls} {};
    ~PlayState() = default;

    virtual void update() override {
        player.input();
        player.update();

        bool foundCol {false};
        for (auto& wall : walls) {
            wall.update();
            Rectangle col = player.GetCollision(wall.GetRect());
            if (col.width > 0 || col.height > 0) {
                foundCol = true;
                player.CorrectCollision(wall.GetRect(), col);
            }
        }
        if (!foundCol) player.setGrounded(false);
    }

    virtual void render() const override {
        DrawTexture(_level1, 0,0, WHITE);
        for (auto& wall : walls) {
            wall.draw(position);
        }
        player.draw(position);
    }
};

#endif