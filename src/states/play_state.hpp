#ifndef _PLAY_STATE_HPP_
#define _PLAY_STATE_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include "state.hpp"
#include "../entities/player.hpp"
#include "../entities/block.hpp"
#include "../entities/coin.hpp"
#include "../texture_loader.hpp"
#include "../resources/levels/level_data.hpp"

class PlayState : public State {
private:
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    LevelType level;
    std::vector<Block> walls;
    std::vector<Coin> coins;
public:
    PlayState(Vector2 pos, LevelType level) : State(pos), player1{std::make_shared<Player>(Vector2{100,100}, Vector2{12,16}, RED, 1)},
        player2{std::make_shared<Player>(Vector2{16,16}, Vector2{12,16}, RED, -1)}, level{level}, walls{}, coins{} {
        switch (level)
        {
        case LEVEL1:
            walls = _level1_data.walls;
            coins = _level1_data.coins;
            break;
        case LEVEL2:
            walls = _level2_data.walls;
            coins = _level2_data.coins;
            break;
        /*case LEVEL3:
            walls = _level3_data.walls;
            coins = _level3_data.coins;
            break;
        case LEVEL4:
            walls = _level4_data.walls;
            coins = _level4_data.coins;
            break;*/
        default:
            walls = _level1_data.walls;
            coins = _level1_data.coins;
            break;
        }
    };
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
        case 3:
            walls = _level3_data.walls;
            coins = _level3_data.coins;
            break;
        case 4:
            walls = _level4_data.walls;
            coins = _level4_data.coins;
            break;
        default:
            walls = _level1_data.walls;
            coins = _level1_data.coins;
            break;
        }
    }

    virtual void update() override {
        player1->input();
        player1->update();

        player2->input();
        player2->update();

        
        bool bounced1 {false};
        bool bounced2 {false};
        Rectangle headCol1 = player1->GetCollision(player2->GetHeadHitBox());
        if (headCol1.x > 0 || (headCol1.y > 0 && !player2->IsTakingDamage())) {
            bounced1 = player1->CalcHeadBounce(headCol1, player2->GetVelocity());
        }
        Rectangle headCol2 = player2->GetCollision(player1->GetHeadHitBox());
        if (headCol2.x > 0 || (headCol2.y > 0 && !player1->IsTakingDamage())) {
            bounced2 = player2->CalcHeadBounce(headCol2, player1->GetVelocity());
        }

        if (bounced1) player2->TakeDamage();
        if (bounced2) player1->TakeDamage();


        bool foundCol1 {false};
        bool foundCol2 {false};
        for (auto& wall : walls) {
            wall.update();

            Rectangle col1 = player1->GetCollision(wall.GetRect());
            if (col1.width > 0 || col1.height > 0) {
                if (bounced1 && player1->GetRect().y < wall.GetRect().y) player1->SetPosition({player1->GetRect().x, wall.GetRect().y + wall.GetRect().height}, position);
                else {
                    foundCol1 = true;
                    player1->CorrectCollision(wall.GetRect(), col1);
                }
            }

            Rectangle col2 = player2->GetCollision(wall.GetRect());
            if (col2.width > 0 || col2.height > 0) {
                if (bounced2 && player2->GetRect().y < wall.GetRect().y) player2->SetPosition({player2->GetRect().x, wall.GetRect().y + wall.GetRect().height}, position);
                else {
                    foundCol2 = true;
                    player2->CorrectCollision(wall.GetRect(), col2);
                }
            }
        }

        if (!foundCol1) {
            player1->setGrounded(false);
        }

        if (!foundCol2) {
            player2->setGrounded(false);
        }

        for (auto& coin : coins) {
            coin.update();

            if (!coin.IsCollected()){
                Rectangle col = player1->GetCollision(coin.GetRect());
                if (col.width > 0 || col.height > 0) {
                    coin.SetCollected();
                }
            }

            if (!coin.IsCollected()){
                Rectangle col = player2->GetCollision(coin.GetRect());
                if (col.width > 0 || col.height > 0) {
                    coin.SetCollected();
                }
            }
        }

        
    }

    virtual void render() const override {
        switch (level)
        {
        case LEVEL1:
            DrawTexture(_level1_data.texture, position.x, position.y, WHITE);
            break;
        case LEVEL2:
            DrawTexture(_level2_data.texture, position.x, position.y, WHITE);
            break;
        case LEVEL3:
            DrawTexture(_level3_data.texture, position.x, position.y, WHITE);
            break;
        case LEVEL4:
            DrawTexture(_level4_data.texture, position.x, position.y, WHITE);
            break;
        default:
            DrawTexture(_level1_data.texture, position.x, position.y, WHITE);
            break;
        }
        //DrawTexture(levelTexture, position.x, position.y, WHITE);
        for (auto& coin : coins) {
            coin.draw(position);
        }
        for (auto& wall : walls) {
            wall.draw(position);
        }
        player1->draw(position);
        player2->draw(position);
    }
};

#endif