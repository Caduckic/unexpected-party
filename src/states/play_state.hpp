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
#include "../ui_layouts.hpp"
#include "../camera_manager.hpp"
#include "../mask_texture.hpp"

/*Rules
1. Coins are enemies
2. Gravity is reverse
3. Coin is mario shell
4. PvP can't stomp
5. Collect most Coins
6. Instant death
7. Level is dark
8. Players are invisible
9. Death is win*/

enum class LevelSpawn {UNKNOWN = -1, UP = 0, RIGHT, DOWN, LEFT};
enum class GameRule {UNKNOWN = -1, ENEMY_COINS = 0, SHELL_COINS, LEVEL_UPSIDE_DOWN, NO_PVP, LOWEST_COINS, INSTANT_DEATH, INVISIBLE_PLAYERS, DIE_TO_WIN, LEVEL_DARK};

class PlayState : public State {
private:
    int roundsLeft;
    int player1Wins {0};
    int player2Wins {0};
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    LevelType level;
    LevelType nextLevel;
    std::vector<Block> walls;
    std::vector<Coin> coins;
    UICanvas pauseMenu;
    bool isPaused;
    LevelSpawn levelSpawn {UNKNOWN};
    Vector2 nextLevelPos {0,0};
    GameRule rule1;
    GameRule rule2;
public:
    PlayState(Vector2 pos, LevelType level) : State(pos), roundsLeft{9}, player1{std::make_shared<Player>(Vector2{100,100}, Vector2{12,16}, 1)},
        player2{std::make_shared<Player>(Vector2{16,16}, Vector2{12,16}, -1)}, level{level}, nextLevel{UNKNOWN_LEVEL}, walls{}, coins{}, pauseMenu{{48,48}, {160, 160}, PAUSE_LAYOUT}, isPaused{false} {
        MaskTexture::Get().ClearTexture();
        switch (level)
        {
        case LEVEL1:
            walls = _level1_data.walls;
            coins = _level1_data.coins;
            player1->SetPosition(_level1_data.player1Pos, {0,0});
            player2->SetPosition(_level1_data.player2Pos, {0,0});
            break;
        case LEVEL2:
            walls = _level2_data.walls;
            coins = _level2_data.coins;
            player1->SetPosition(_level2_data.player1Pos, {0,0});
            player2->SetPosition(_level2_data.player2Pos, {0,0});
            break;
        case LEVEL3:
            walls = _level3_data.walls;
            coins = _level3_data.coins;
            player1->SetPosition(_level3_data.player1Pos, {0,0});
            player2->SetPosition(_level3_data.player2Pos, {0,0});
            break;
        case LEVEL4:
            walls = _level4_data.walls;
            coins = _level4_data.coins;
            player1->SetPosition(_level4_data.player1Pos, {0,0});
            player2->SetPosition(_level4_data.player2Pos, {0,0});
            break;
        default:
            walls = _level1_data.walls;
            coins = _level1_data.coins;
            player1->SetPosition(_level1_data.player1Pos, {0,0});
            player2->SetPosition(_level1_data.player2Pos, {0,0});
            break;
        }

        SetRandomRules();
        if (rule1 == GameRule::ENEMY_COINS || rule2 == GameRule::ENEMY_COINS) {
            for (auto &coin : coins) {
                coin.SetMode(CoinMode::ENEMY);
            }
        }
        else if (rule1 == GameRule::SHELL_COINS || rule2 == GameRule::SHELL_COINS) {
            for (auto &coin : coins) {
                coin.SetMode(CoinMode::SHELL);
            }
        }
    };
    ~PlayState() = default;

    GameState GetGameState() override {
        return PLAY;
    }

    virtual void setPosition(const Vector2 pos) {
        position = pos;
        if (pos.x == 0 && pos.y == 0) {
            if (rule1 == GameRule::LEVEL_UPSIDE_DOWN || rule2 == GameRule::LEVEL_UPSIDE_DOWN) {
                CameraManager::Get().RotateCam(180);
            }
            else CameraManager::Get().RotateCam(0);
        }
    }

    void SetRandomRules() {
        rule1 = (GameRule)GetRandomValue(0, 8);
        rule2 = (GameRule)GetRandomValue(0, 8);
        while (rule2 == rule1 || ((rule1 == GameRule::ENEMY_COINS || rule1 == GameRule::SHELL_COINS) && (rule2 == GameRule::ENEMY_COINS || rule2 == GameRule::SHELL_COINS))) {
            rule2 = (GameRule)GetRandomValue(0, 8);
        }
    }

    virtual const UICanvas& GetCurrentCanvas() const override {
        return pauseMenu;
    }

    int GetLevelNum() {
        return level;
    }

    int GetRoundsLeft() {
        return roundsLeft;
    }

    void UnloadLevel() {
        walls.clear();
        coins.clear();
    }

    void LoadLevel(int loadLevel) {
        UnloadLevel();
        CameraManager::Get().RotateCam(0);
        player1->Reset();
        player2->Reset();
        switch (loadLevel)
        {
        case 1:
            walls = _level1_data.walls;
            coins = _level1_data.coins;
            player1->SetPosition(_level1_data.player1Pos, position);
            player2->SetPosition(_level1_data.player2Pos, position);
            level = LEVEL1;
            break;
        case 2:
            walls = _level2_data.walls;
            coins = _level2_data.coins;
            player1->SetPosition(_level2_data.player1Pos, position);
            player2->SetPosition(_level2_data.player2Pos, position);
            level = LEVEL2;
            break;
        case 3:
            walls = _level3_data.walls;
            coins = _level3_data.coins;
            player1->SetPosition(_level3_data.player1Pos, position);
            player2->SetPosition(_level3_data.player2Pos, position);
            level = LEVEL3;
            break;
        case 4:
            walls = _level4_data.walls;
            coins = _level4_data.coins;
            player1->SetPosition(_level4_data.player1Pos, position);
            player2->SetPosition(_level4_data.player2Pos, position);
            level = LEVEL4;
            break;
        default:
            walls = _level1_data.walls;
            coins = _level1_data.coins;
            player1->SetPosition(_level1_data.player1Pos, position);
            player2->SetPosition(_level1_data.player2Pos, position);
            level = LEVEL1;
            break;
        }

        SetRandomRules();
        if (rule1 == GameRule::ENEMY_COINS || rule2 == GameRule::ENEMY_COINS) {
            for (auto &coin : coins) {
                coin.SetMode(CoinMode::ENEMY);
            }
        }
        else if (rule1 == GameRule::SHELL_COINS || rule2 == GameRule::SHELL_COINS) {
            for (auto &coin : coins) {
                coin.SetMode(CoinMode::SHELL);
            }
        }
    }

    void SetRandomLevel() {
        CameraManager::Get().RotateCam(0);
        MaskTexture::Get().ClearTexture();
        roundsLeft -= 1;
        int randomLevel {GetRandomValue(1, 4)};

        while (randomLevel == level) {
            randomLevel = GetRandomValue(1, 4);
        }

        if (randomLevel == 1) nextLevel = LEVEL1;
        else if (randomLevel == 2) nextLevel = LEVEL2;
        else if (randomLevel == 3) nextLevel = LEVEL3;
        else if (randomLevel == 4) nextLevel = LEVEL4;

        int dir {GetRandomValue(0, 3)};
        nextLevelPos = {0, -256};
        switch (dir)
        {
        case 0:
            nextLevelPos = {0, -256};
            levelSpawn = LevelSpawn::UP;
            break;
        case 1:
            nextLevelPos = {256, 0};
            levelSpawn = LevelSpawn::RIGHT;
            break;
        case 2:
            nextLevelPos = {0, 256};
            levelSpawn = LevelSpawn::DOWN;
            break;
        case 3:
            nextLevelPos = {-256, 0};
            levelSpawn = LevelSpawn::LEFT;
            break;
        default:
            break;
        }
    }

    void SetLevel() {
        position = {0,0};
        LoadLevel(nextLevel);
        nextLevel = UNKNOWN_LEVEL;

        if (rule1 == GameRule::LEVEL_UPSIDE_DOWN || rule2 == GameRule::LEVEL_UPSIDE_DOWN) {
            CameraManager::Get().RotateCam(180);
        } else CameraManager::Get().RotateCam(0);
    }

    void TransitionLevel() {
        switch (levelSpawn)
        {
        case LevelSpawn::UP:
            nextLevelPos.y += 180 * GetFrameTime();
            position.y = nextLevelPos.y + 256;
            if (nextLevelPos.y > 0) {
                SetLevel();
            }
            break;
        case LevelSpawn::RIGHT:
            nextLevelPos.x -= 180 * GetFrameTime();
            position.x = nextLevelPos.x - 256;
            if (nextLevelPos.x < 0) {
                SetLevel();
            }
            break;
        case LevelSpawn::DOWN:
            nextLevelPos.y -= 180 * GetFrameTime();
            position.y = nextLevelPos.y - 256;
            if (nextLevelPos.y < 0) {
                SetLevel();
            }
            break;
        case LevelSpawn::LEFT:
            nextLevelPos.x += 180 * GetFrameTime();
            position.x = nextLevelPos.x + 256;
            if (nextLevelPos.x > 0) {
                SetLevel();
            }
            break;
        default:
            SetLevel();
            break;
        }
    }

    virtual void update() override {
        if (IsKeyPressed(KEY_K)) {
            SetRandomLevel();
        }
        if (nextLevel == UNKNOWN_LEVEL) {
            if (IsKeyPressed(KEY_P)) {
                isPaused = !isPaused;
            }

            if (!isPaused) {
                player1->input();
                if (rule1 == GameRule::LEVEL_UPSIDE_DOWN || rule2 == GameRule::LEVEL_UPSIDE_DOWN) {
                    player1->SetDirection(-player1->GetDirection());
                }
                player1->update();

                player2->input();
                if (rule1 == GameRule::LEVEL_UPSIDE_DOWN || rule2 == GameRule::LEVEL_UPSIDE_DOWN) {
                    player2->SetDirection(-player2->GetDirection());
                }
                player2->update();
                
                bool bounced1 {false};
                bool bounced2 {false};
                Rectangle headCol1 = player1->GetCollision(player2->GetHeadHitBox());
                if ((headCol1.x > 0 || (headCol1.y > 0 && !player2->IsTakingDamage())) && !player1->IsGrounded()) {
                    bounced1 = player1->CalcHeadBounce(headCol1, player2->GetVelocity());
                }
                Rectangle headCol2 = player2->GetCollision(player1->GetHeadHitBox());
                if ((headCol2.x > 0 || (headCol2.y > 0 && !player1->IsTakingDamage())) && !player2->IsGrounded()) {
                    bounced2 = player2->CalcHeadBounce(headCol2, player1->GetVelocity());
                }

                if (rule1 != GameRule::NO_PVP && rule2 != GameRule::NO_PVP) {
                    if (bounced1) player2->TakeDamage();
                    if (bounced2) player1->TakeDamage();
                }


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
                    player1->SetGrounded(false);
                }

                if (!foundCol2) {
                    player2->SetGrounded(false);
                }

                for (auto& coin : coins) {
                    coin.update();
                    if (coin.GetMode() == CoinMode::ENEMY || coin.GetMode() == CoinMode::SHELL) {
                        bool foundCol {false};
                        for (auto& wall : walls) {
                            Rectangle col = coin.GetCollision(wall.GetRect());
                            if (col.width > 0 || col.height > 0) {
                                foundCol = true;
                                coin.CorrectCollision(wall.GetRect(), col);
                            }
                        }
                        if (!coin.IsCollected()){
                            for (auto& otherCoin : coins) {
                                if (otherCoin != coin && !otherCoin.IsCollected()) {
                                    Rectangle col = coin.GetCollision(otherCoin.GetRect());
                                    if (col.width > 0 || col.height > 0) {
                                        foundCol = true;
                                        coin.CorrectCollision(otherCoin.GetRect(), col);
                                        if (coin.IsColX()) {
                                            if (otherCoin.IsBounced()) {
                                                otherCoin.Bounce(coin.GetCurrentDirection());
                                            }
                                            else {
                                                otherCoin.Bounce(-coin.GetCurrentDirection());
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if (!foundCol) {
                            coin.SetGrounded(false);
                        }
                    }
                    if (!coin.IsCollected()){
                        Rectangle col = player1->GetCollision(coin.GetRect());
                        if (col.width > 0 || col.height > 0) {
                            if (coin.GetMode() != CoinMode::SHELL) coin.SetCollected();
                            if (coin.GetMode() == CoinMode::ENEMY || coin.GetMode() == CoinMode::SHELL) {
                                bool bounced = player1->CalcHeadBounce(col, {0,0});
                                if (!bounced && coin.GetMode() == CoinMode::SHELL && !coin.IsBounced()) coin.SetCollected();
                                else if (!bounced && (coin.GetMode() == CoinMode::ENEMY || (coin.GetMode() == CoinMode::SHELL && coin.IsBounced()))) player1->TakeDamage();
                                else {
                                    player1->StopTakeDamage();
                                    if (coin.GetMode() == CoinMode::SHELL) {
                                        coin.Bounce(player1->GetCurrentDirection());
                                    }
                                }
                            }
                        }
                    }

                    if (!coin.IsCollected()){
                        Rectangle col = player2->GetCollision(coin.GetRect());
                        if (col.width > 0 || col.height > 0) {
                            if (coin.GetMode() != CoinMode::SHELL) coin.SetCollected();
                            if (coin.GetMode() == CoinMode::ENEMY || coin.GetMode() == CoinMode::SHELL) {
                                bool bounced = player2->CalcHeadBounce(col, {0,0});
                                if (!bounced && coin.GetMode() == CoinMode::SHELL && !coin.IsBounced()) coin.SetCollected();
                                else if (!bounced && (coin.GetMode() == CoinMode::ENEMY || (coin.GetMode() == CoinMode::SHELL && coin.IsBounced()))) player2->TakeDamage();
                                else {
                                    player2->StopTakeDamage();
                                    if (coin.GetMode() == CoinMode::SHELL) {
                                        coin.Bounce(player2->GetCurrentDirection());
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else {
                pauseMenu.update();
            }

            if (rule1 == GameRule::LEVEL_DARK || rule2 == GameRule::LEVEL_DARK){
                Vector2 player1Mask {player1->GetRect().x + (player1->GetRect().width / 2), player1->GetRect().y + (player1->GetRect().height / 2)};
                Vector2 player2Mask {player2->GetRect().x + (player2->GetRect().width / 2), player2->GetRect().y + (player2->GetRect().height / 2)};

                MaskTexture::Get().MaskAroundPlayers(player1Mask, player2Mask);
            }
        }
        else {
            TransitionLevel();
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

        switch (nextLevel)
        {
        case LEVEL1:
            DrawTexture(_level1_data.texture, nextLevelPos.x, nextLevelPos.y, WHITE);
            break;
        case LEVEL2:
            DrawTexture(_level2_data.texture, nextLevelPos.x, nextLevelPos.y, WHITE);
            break;
        case LEVEL3:
            DrawTexture(_level3_data.texture, nextLevelPos.x, nextLevelPos.y, WHITE);
            break;
        case LEVEL4:
            DrawTexture(_level4_data.texture, nextLevelPos.x, nextLevelPos.y, WHITE);
            break;
        default:
            //DrawTexture(_level1_data.texture, position.x + 256, position.y, WHITE);
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

        MaskTexture::Get().DrawTexture();

        //DrawTextEx(ROMULUS_FONT, "test TEST", {0,0},40, 2, BLUE);
        if (isPaused) {
            DrawTexture(_pause_canvas, position.x + 48, position.y + 48, WHITE);
            pauseMenu.draw(position);
        }
    }
};

#endif