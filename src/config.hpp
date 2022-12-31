#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include "raylib.h"
#include <map>

const Vector2 SCREEN_SIZE {256, 256};
const float START_GRAVITY {400}, MAX_GRAVITY {500};
const float PLAYER_ACCELERATION {50}, PLAYER_MAX_SPEED {100}, PLAYER_JUMP {-208}, PLAYER_BOUNCE {-184};
const float COIN_MAX_SPEED {40}, SHELL_COIN_MAX_SPEED {80};

const int TARGET_FPS {240};

const Color _COLOR3 {48,98,48,255};

Font ROMULUS_FONT;

void LoadGameFont() {
    ROMULUS_FONT = LoadFont("resources/fonts/romulus.png");
}

void UnloadGameFont() {
    UnloadFont(ROMULUS_FONT);
}

#endif