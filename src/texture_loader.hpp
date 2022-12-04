#ifndef _TEXTURE_LOADER_HPP_
#define _TEXTURE_LOADER_HPP_

#include "raylib.h"

Texture2D _level1;
Texture2D _level2;
Texture2D _player1_tilemap;
Texture2D _player2_tilemap;
Texture2D _coin_tilemap;

void LoadAllTextures() {
    _level1 = LoadTexture("./resources/sprites/level_1.png");
    _level2 = LoadTexture("./resources/sprites/level_2.png");
    _player1_tilemap = LoadTexture("./resources/sprites/player_1.png");
    _player2_tilemap = LoadTexture("./resources/sprites/player_2.png");
    _coin_tilemap = LoadTexture("./resources/sprites/coin.png");
}

void UnloadAllTextures() {
    UnloadTexture(_level1);
    UnloadTexture(_level2);
    UnloadTexture(_player1_tilemap);
    UnloadTexture(_player2_tilemap);
    UnloadTexture(_coin_tilemap);
}

#endif