#ifndef _STATE_MANAGER_HPP_
#define _STATE_MANAGER_HPP_

#include "state.hpp"
#include "title_state.hpp"
#include "play_state.hpp"
#include <memory>

enum GameState {UNKNOWN = -1, TITLE = 0, OPTIONS, PLAY, ENDING};

class StateManager {
private:
    StateManager() : currentState{std::make_shared<PlayState>(Vector2{0,0}, LEVEL1)}, nextState{nullptr}, stateTransitioning{false} {};
    static StateManager instance;
    std::shared_ptr<State> currentState;
    std::shared_ptr<State> nextState;
    bool stateTransitioning;
public:
    static StateManager& Get() {
        return instance;
    }
    StateManager(const StateManager&) = delete;
    ~StateManager() = default;

    void LoadNextState(GameState state) {
        int dir {GetRandomValue(0, 3)};
        Vector2 startPos {0, -256};
        switch (dir)
        {
        case 0:
            startPos = {0, -256};
            break;
        case 1:
            startPos = {256, 0};
            break;
        case 2:
            startPos = {0, 256};
            break;
        case 3:
            startPos = {-256, 0};
            break;
        default:
            break;
        }

        int level {GetRandomValue(1, 4)};
        LevelType nextLevel;
        switch (level)
        {
        case LEVEL1:
            nextLevel = LEVEL1;
            break;
        case LEVEL2:
            nextLevel = LEVEL2;
            break;
        case LEVEL3:
            nextLevel = LEVEL3;
            break;
        case LEVEL4:
            nextLevel = LEVEL4;
            break;
        default:
            nextLevel = LEVEL1;
            break;
        }

        switch (state)
        {
        case TITLE:
            nextState.reset(std::make_shared<TitleState>(startPos).get());
            break;
        case PLAY:
            nextState = std::make_shared<PlayState>(startPos, nextLevel);
            break;
        default:
            nextState.reset(std::make_shared<PlayState>(startPos, nextLevel).get());
            break;
        }
        stateTransitioning = true;
    }

    void update() {
        if (IsKeyPressed(KEY_L)) LoadNextState(PLAY);
        if (!stateTransitioning)
            currentState->update();
        else {
            Vector2 nextStatePos = nextState->getPosition();

            if (nextStatePos.x != 0) {
                if (nextStatePos.x > 1) {
                    nextState->setPosition({nextStatePos.x - 180 * GetFrameTime(), 0});
                    currentState->setPosition({(nextStatePos.x - 180 * GetFrameTime()) - 256, 0});
                }
                else if (nextStatePos.x < -1) {
                    nextState->setPosition({nextStatePos.x + 180 * GetFrameTime(), 0});
                    currentState->setPosition({(nextStatePos.x + 180 * GetFrameTime()) + 256, 0});
                }

                if (nextStatePos.x < 1 && nextStatePos.x > -1) {
                    currentState.swap(nextState);
                    nextState.reset();
                    currentState->setPosition({0,0});
                    stateTransitioning = false;
                }
            }
            else if (nextStatePos.y != 0) {
                if (nextStatePos.y > 1) {
                    nextState->setPosition({ 0, nextStatePos.y - 180 * GetFrameTime()});
                    currentState->setPosition({ 0, ( nextStatePos.y - 180 * GetFrameTime()) - 256});
                }
                else if (nextStatePos.y < -1) {
                    nextState->setPosition({ 0, nextStatePos.y + 180 * GetFrameTime()});
                    currentState->setPosition({ 0, (nextStatePos.y + 180 * GetFrameTime()) + 256});
                }

                if (nextStatePos.y < 1 && nextStatePos.y > -1) {
                    currentState.swap(nextState);
                    //currentState = std::move(nextState);
                    nextState.reset();
                    currentState->setPosition({0,0});
                    stateTransitioning = false;
                }
            }
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