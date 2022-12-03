#ifndef _TEXTURE_LOADER_HPP_
#define _TEXTURE_LOADER_HPP_

#include "raylib.h"

Texture2D _level1;
Texture2D _player1_tilemap;
Texture2D _player2_tilemap;
Texture2D _coin_tilemap;

void LoadAllTextures() {
    _level1 = LoadTexture("./resources/sprites/level_1.png");
    _player1_tilemap = LoadTexture("./resources/sprites/player_1.png");
    _player2_tilemap = LoadTexture("./resources/sprites/player_2.png");
    _coin_tilemap = LoadTexture("./resources/sprites/coin.png");
}

void UnloadAllTextures() {
    UnloadTexture(_level1);
    UnloadTexture(_player1_tilemap);
}

#endif