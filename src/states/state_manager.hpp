#ifndef _STATE_MANAGER_HPP_
#define _STATE_MANAGER_HPP_

#include "state.hpp"
#include "title_state.hpp"
#include "play_state.hpp"
#include <memory>

enum GameState {UNKNOWN = -1, TITLE = 0, OPTIONS, PLAY, ENDING};

class StateManager {
private:
    StateManager() : currentState{std::make_shared<PlayState>(Vector2{0,0})}, nextState{nullptr}, stateTransitioning{false} {};
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

        switch (state)
        {
        case TITLE:
            nextState.reset(std::make_shared<TitleState>(startPos).get());
            break;
        case PLAY:
            nextState.reset(std::make_shared<PlayState>(startPos).get());
            break;
        default:
            nextState.reset(std::make_shared<PlayState>(startPos).get());
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
                    nextState->setPosition({nextStatePos.x - 200 * GetFrameTime(), 0});
                    currentState->setPosition({(nextStatePos.x - 200 * GetFrameTime()) - 256, 0});
                }
                else if (nextStatePos.x < -1) {
                    nextState->setPosition({nextStatePos.x + 200 * GetFrameTime(), 0});
                    currentState->setPosition({(nextStatePos.x + 200 * GetFrameTime()) + 256, 0});
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
                    nextState->setPosition({ 0, nextStatePos.y - 200 * GetFrameTime()});
                    currentState->setPosition({ 0, ( nextStatePos.y - 200 * GetFrameTime()) - 256});
                }
                else if (nextStatePos.y < -1) {
                    nextState->setPosition({ 0, nextStatePos.y + 200 * GetFrameTime()});
                    currentState->setPosition({ 0, (nextStatePos.y + 200 * GetFrameTime()) + 256});
                }

                if (nextStatePos.y < 1 && nextStatePos.y > -1) {
                    currentState.swap(nextState);
                    nextState.reset();
                    currentState->setPosition({0,0});
                    stateTransitioning = false;
                }
            }
        }
    }

    void render() {
        currentState->render();
    }
};

StateManager StateManager::instance;

#endif