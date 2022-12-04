#ifndef _PLAY_STATE_HPP_
#define _PLAY_STATE_HPP_

#include <vector>
#include "state.hpp"
#include "../entities/player.hpp"
#include "../entities/block.hpp"
#include "../entities/coin.hpp"
#include "../texture_loader.hpp"
#include "../resources/levels/level_data.hpp"

class PlayState : public State {
private:
    Player player;
    std::vector<Block> walls;
    std::vector<Coin> coins;
public:
    PlayState(Vector2 pos) : State(pos), player{{100,100}, {12,16}, RED, 1}, walls{_level1_data.walls}, coins{_level1_data.coins} {};
    ~PlayState() = default;

    void UnloadLevel() {
        walls.clear();
        coins.clear();
    }

    void LoadLevel(int level) {
        UnloadLevel();
        switch (level)
        {
        case 1:
            walls = _level1_data.walls;
            coins = _level1_data.coins;
            break;
        case 2:
            walls = _level2_data.walls;
            coins = _level2_data.coins;
            break;
        /*case 3:
            walls = _level3_data.walls;
            coins = _level3_data.coins;
            break;
        case 4:
            walls = _level4_data.walls;
            coins = _level4_data.coins;
            break;*/
        default:
            walls = _level1_data.walls;
            coins = _level1_data.coins;
            break;
        }
    }

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
        for (auto& coin : coins) {
            coin.update();

            if (!coin.IsCollected()){
                Rectangle col = player.GetCollision(coin.GetRect());
                if (col.width > 0 || col.height > 0) {
                    coin.SetCollected();
                }
            }
        }
        if (!foundCol) player.setGrounded(false);
    }

    virtual void render() const override {
        DrawTexture(_level1, 0,0, WHITE);
        for (auto& coin : coins) {
            coin.draw(position);
        }
        for (auto& wall : walls) {
            wall.draw(position);
        }
        player.draw(position);
    }
};

#endif