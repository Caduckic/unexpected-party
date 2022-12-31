#ifndef _STATE_MANAGER_HPP_
#define _STATE_MANAGER_HPP_

#include "state.hpp"
#include "title_state.hpp"
#include "play_state.hpp"
#include <memory>

enum class StateSpawn {UNKNOWN = -1, UP = 0, RIGHT, DOWN, LEFT};

class StateManager {
private:
    StateManager() : currentState{std::make_shared<TitleState>(Vector2{0,0})}, nextState{nullptr}, stateTransitioning{false}, isQuitGame{false} {};
    static StateManager instance;
    std::shared_ptr<State> currentState;
    std::shared_ptr<State> nextState;
    StateSpawn nextStateSpawn {StateSpawn::UNKNOWN};
    bool stateTransitioning;
    bool isQuitGame;
public:
    static StateManager& Get() {
        return instance;
    }
    StateManager(const StateManager&) = delete;
    ~StateManager() = default;

    bool IsQuitGame() {
        return isQuitGame;
    }

    void QuitGame() {
        isQuitGame = true;
    }

    void LoadNextState(GameState state) {
        int dir {GetRandomValue(0, 3)};
        Vector2 startPos {0, -256};
        switch (dir)
        {
        case 0:
            startPos = {0, -256};
            nextStateSpawn = StateSpawn::UP;
            break;
        case 1:
            startPos = {256, 0};
            nextStateSpawn = StateSpawn::RIGHT;
            break;
        case 2:
            startPos = {0, 256};
            nextStateSpawn = StateSpawn::DOWN;
            break;
        case 3:
            startPos = {-256, 0};
            nextStateSpawn = StateSpawn::LEFT;
            break;
        default:
            break;
        }

        switch (state)
        {
        case TITLE:
            nextState = std::make_shared<TitleState>(startPos);
            break;
        case PLAY: {
            int level {GetRandomValue(1, 4)};

            while (level == currentState->GetLevelNum()) {
                level = GetRandomValue(1, 4);
            }

            LevelType nextLevel;

            if (level == 1) nextLevel = LEVEL1;
            else if (level == 2) nextLevel = LEVEL2;
            else if (level == 3) nextLevel = LEVEL3;
            else if (level == 4) nextLevel = LEVEL4;

            nextState = std::make_shared<PlayState>(startPos, nextLevel);
            break;
        }
        default:
            nextState = std::make_shared<PlayState>(startPos, LEVEL1);
            break;
        }
        stateTransitioning = true;
    }

    void SwapState() {
        currentState.swap(nextState);
        nextState.reset();
        currentState->setPosition({0,0});
        stateTransitioning = false;
    }

    void TransitionState() {
        //Vector2 nextStatePos = nextState->getPosition();

        switch (nextStateSpawn)
        {
        case StateSpawn::UP:
            nextState->setPosition({0, nextState->getPosition().y + 180 * GetFrameTime()});
            currentState->setPosition({0, nextState->getPosition().y + 256});
            if (nextState->getPosition().y > 0) {
                SwapState();
            }
            break;
        case StateSpawn::RIGHT:
            nextState->setPosition({nextState->getPosition().x - 180 * GetFrameTime(), 0});
            currentState->setPosition({nextState->getPosition().x - 256, 0});
            if (nextState->getPosition().x < 0) {
                SwapState();
            }
            break;
        case StateSpawn::DOWN:
            nextState->setPosition({0, nextState->getPosition().y - 180 * GetFrameTime()});
            currentState->setPosition({0, nextState->getPosition().y - 256});
            if (nextState->getPosition().y < 0) {
                SwapState();
            }
            break;
        case StateSpawn::LEFT:
            nextState->setPosition({nextState->getPosition().x + 180 * GetFrameTime(), 0});
            currentState->setPosition({nextState->getPosition().x + 256, 0});
            if (nextState->getPosition().x > 0) {
                SwapState();
            }
            break;
        default:
            SwapState();
            break;
        }
    }

    void update() {
        if (IsKeyPressed(KEY_L)) LoadNextState(PLAY);
        else if (IsKeyPressed(KEY_T)) LoadNextState(TITLE);
        if (!stateTransitioning) {
            currentState->update();
            for (const auto &button : currentState->GetCurrentCanvas().GetButtons()) {
                
                if (button.second.IsPressed()) {
                    UIAction action = button.second.GetAction();

                    switch (action)
                    {
                    case UIAction::GOTO_PLAY:
                        LoadNextState(PLAY);
                        break;
                    case UIAction::GOTO_TITLE:
                        LoadNextState(TITLE);
                        break;
                    case UIAction::QUIT_GAME:
                        QuitGame();
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        else {
            TransitionState();
        }
    }

    void render() {
        currentState->render();
        if (stateTransitioning) nextState->render();
        //DrawText(std::to_string(currentState->getPosition().y).c_str(), 0,0,30,BLUE);
    }
};

StateManager StateManager::instance;

#endif