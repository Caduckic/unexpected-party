#ifndef _TEXTURE_LOADER_HPP_
#define _TEXTURE_LOADER_HPP_

#include "raylib.h"

Texture2D _player1_tilemap;
Texture2D _player2_tilemap;
Texture2D _coin_tilemap;
Texture2D _title_screen;

void LoadAllTextures() {
    _player1_tilemap = LoadTexture("./resources/sprites/player_1.png");
    _player2_tilemap = LoadTexture("./resources/sprites/player_2.png");
    _coin_tilemap = LoadTexture("./resources/sprites/coin.png");
    _title_screen = LoadTexture("./resources/sprites/title_screen.png");
}

void UnloadAllTextures() {
    UnloadTexture(_player1_tilemap);
    UnloadTexture(_player2_tilemap);
    UnloadTexture(_coin_tilemap);
    UnloadTexture(_title_screen);
}

#endif