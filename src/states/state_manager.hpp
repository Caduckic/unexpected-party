#ifndef _STATE_MANAGER_HPP_
#define _STATE_MANAGER_HPP_

#include "state.hpp"
#include "title_state.hpp"
#include "play_state.hpp"
#include <memory>

enum GameStates {UNKNOWN = -1, TITLE = 0, OPTIONS, GAMEPLAY, ENDING};

class StateManager {
private:
    StateManager() : currentState{std::make_shared<PlayState>(Vector2{0,0})}, nextState{nullptr} {};
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

    void LoadNextState() {

    }

    void update() {
        currentState->update();
    }

    void render() {
        currentState->render();
    }
};

StateManager StateManager::instance;

#endif