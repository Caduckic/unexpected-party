#ifndef _UI_LAYOUTS_HPP_
#define _UI_LAYOUTS_HPP_

#include <map>
#include "./entities/ui_button.hpp"

std::map<int, UIButton> TITLE_LAYOUT = {
    {0, {{80, 112}, {96, 16}, "PLAY GAME", UIAction::GOTO_PLAY, true}},
    {1, {{80, 144}, {96, 16}, "QUIT GAME", UIAction::QUIT_GAME}}
};

std::map<int, UIButton> PAUSE_LAYOUT = {
    {0, {{48,48}, {48, 16}, "QUIT", UIAction::GOTO_TITLE}},
};

#endif