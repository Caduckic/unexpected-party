#ifndef _PLAY_STATE_HPP_
#define _PLAY_STATE_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include "state.hpp"
#include "../entities/player.hpp"
#include "../entities/new_player.hpp"
#include "../entities/block.hpp"
#include "../entities/coin.hpp"
#include "../entities/entity_object.hpp"
#include "../texture_loader.hpp"
#include "../resources/levels/level_data.hpp"
#include "../ui_layouts.hpp"

class PlayState : public State {
private:
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    NewPlayer player3;
    EntityObject entity {{32,32}, {16,16}, 1};
    LevelType level;
    std::vector<Block> walls;
    std::vector<Coin> coins;
    UICanvas pauseMenu;
    bool isPaused;
public:
    PlayState(Vector2 pos, LevelType level) : State(pos), player1{std::make_shared<Player>(Vector2{100,100}, Vector2{12,16}, RED, 1)},
        player2{std::make_shared<Player>(Vector2{16,16}, Vector2{12,16}, RED, -1)}, player3{{64,64}, {12,16}, 1}, level{level}, walls{}, coins{}, pauseMenu{{48,48}, {256, 256}, PAUSE_LAYOUT}, isPaused{false} {
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
        case LEVEL3:
            walls = _level3_data.walls;
            coins = _level3_data.coins;
            break;
        case LEVEL4:
            walls = _level4_data.walls;
            coins = _level4_data.coins;
            break;
        default:
            walls = _level1_data.walls;
            coins = _level1_data.coins;
            break;
        }
    };
    ~PlayState() = default;

    GameState GetGameState() override {
        return PLAY;
    }

    virtual const UICanvas& GetCurrentCanvas() const override {
        return pauseMenu;
    }

    int GetLevelNum() {
        return level;
    }

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
        if (IsKeyPressed(KEY_P)) {
            isPaused = !isPaused;
        }

        if (!isPaused) {
            pauseMenu.update();

            player1->input();
            player1->update();

            player2->input();
            player2->update();

            player3.input();
            player3.update();

            entity.input();
            entity.update();
            
            bool bounced1 {false};
            bool bounced2 {false};
            bool bounced3 {false};
            Rectangle headCol1 = player1->GetCollision(player2->GetHeadHitBox());
            if (headCol1.x > 0 || (headCol1.y > 0 && !player2->IsTakingDamage())) {
                bounced1 = player1->CalcHeadBounce(headCol1, player2->GetVelocity());
            }
            Rectangle headCol2 = player2->GetCollision(player1->GetHeadHitBox());
            if (headCol2.x > 0 || (headCol2.y > 0 && !player1->IsTakingDamage())) {
                bounced2 = player2->CalcHeadBounce(headCol2, player1->GetVelocity());
            }
            Rectangle headCol3 = player2->GetCollision(player3.GetHeadHitBox());
            if (headCol3.width > 0 || (headCol3.height > 0 && !player3.IsTakingDamage())) {
                std::cout << player3.GetHeadHitBox().width << ", " <<headCol3.height << std::endl;
                bounced3 = player2->CalcHeadBounce(headCol3, player3.GetVelocity());
            }

            if (bounced1) player2->TakeDamage();
            if (bounced2) player1->TakeDamage();
            if (bounced3) player3.TakeDamage();


            bool foundCol1 {false};
            bool foundCol2 {false};
            bool foundCol3 {false};
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

                Rectangle col3 = entity.GetCollision(wall.GetRect());
                if (col3.width > 0 || col3.height > 0) {
                        foundCol2 = true;
                        entity.CorrectCollision(wall.GetRect(), col3);
                }

                Rectangle col4 = player3.GetCollision(wall.GetRect());
                if (col4.width > 0 || col4.height > 0) {
                    //if (bounced2 && player3.GetRect().y < wall.GetRect().y) player3.SetPosition({player3.GetRect().x, wall.GetRect().y + wall.GetRect().height}, position);
                    //else {
                        foundCol3 = true;
                        player3.CorrectCollision(wall.GetRect(), col4);
                    //}
                }
            }

            if (!foundCol1) {
                player1->setGrounded(false);
            }

            if (!foundCol2) {
                player2->setGrounded(false);
            }

            if (!foundCol3) {
                player3.SetGrounded(false);
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
        else {
            pauseMenu.update();
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
        player3.draw(position);

        //DrawTextEx(ROMULUS_FONT, "test TEST", {0,0},40, 2, BLUE);
        if (isPaused) {
            DrawTexture(_pause_canvas, position.x + 48, position.y + 48, WHITE);
            pauseMenu.draw(position);
        }

        entity.draw(position);
    }
};

#endif