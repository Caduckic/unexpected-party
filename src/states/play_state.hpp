#ifndef _PLAY_STATE_HPP_
#define _PLAY_STATE_HPP_

#include <vector>
#include "state.hpp"
#include "../entities/player.hpp"
#include "../entities/block.hpp"

class PlayState : public State {
private:
    Player player;
    std::vector<Block> walls;
public:
    PlayState(Vector2 pos) : State(pos), player{{100,100}, {8,12}, RED}, walls{{{180, 100}, {50, 30}, RED}, {{0, 256 - 30}, {256, 30}, RED}, {{256 - 30,0}, {30, 256}, RED}} {};
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
        for (auto& wall : walls) {
            wall.draw(position);
        }
        player.draw(position);
    }
};

#endif