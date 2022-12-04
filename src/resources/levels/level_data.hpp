#ifndef _LEVEL1_DATA_HPP_
#define _LEVEL1_DATA_HPP_

#include "../../entities/block.hpp"
#include "../../entities/coin.hpp"
#include "../../texture_loader.hpp"
#include <vector>

enum LevelType {UNKNOWN_LEVEL = -1, LEVEL1 = 1, LEVEL2, LEVEL3, LEVEL4};

struct LevelData
{
    Texture2D texture;
    std::vector<Block> walls;
    std::vector<Coin> coins;
};

LevelData _level1_data {
    {},
    {
        { { 0, 0 }, { 16, 256} },
        { { 16, 0 }, { 224, 16} },
        { { 16, 240 }, { 224, 16} },
        { { 240, 0 }, { 16, 256} },

        { { 16, 64 }, { 80, 16} },
        { { 16, 192 }, { 64, 16} },
        { { 112, 144 }, { 80, 16} },
        { { 160, 96 }, { 80, 16} },
    },
    {
        {{ 128, 128 }},
        {{ 144, 128 }},
        {{ 160, 128 }},

        {{ 16, 160 }},
        {{ 32, 160 }},
        {{ 48, 160 }},
        {{ 16, 176 }},
        {{ 32, 176 }},
        {{ 48, 176 }},

        {{ 160, 192 }},
        {{ 176, 192 }},
        {{ 192, 192 }},
        {{ 208, 192 }},
        {{ 224, 192 }},
        {{ 160, 208 }},
        {{ 176, 208 }},
        {{ 192, 208 }},
        {{ 208, 208 }},
        {{ 224, 208 }},
        {{ 160, 224 }},
        {{ 176, 224 }},
        {{ 192, 224 }},
        {{ 208, 224 }},
        {{ 224, 224 }}
    }
};

LevelData _level2_data {
    {},
    {
        { { 0, 0 }, { 16, 256} },
        { { 16, 0 }, { 224, 16} },
        { { 16, 240 }, { 224, 16} },
        { { 240, 0 }, { 16, 256} },

        { { 16, 80 }, { 80, 16 } },
        { { 144, 80 }, { 80, 16 } },

        { { 80, 96 }, { 16, 32 } },
        { { 144, 96 }, { 16, 32 } },

        { { 112, 112 }, { 16, 16 } },
        { { 208, 112 }, { 32, 16 } },

        { { 16, 160 }, { 96, 16 } },
        { { 160, 160 }, { 80, 16 } },

        { { 96, 176 }, { 16, 48 } },
        { { 160, 176 }, { 16, 48 } },

        { { 128, 208 }, { 16, 32 } },
    },
    {
        {{ 112, 32 }},
        {{ 112, 48 }},

        {{ 208, 96 }},

        {{ 16, 112 }},
        {{ 32, 112 }},
        {{ 48, 112 }},
        {{ 16, 128 }},
        {{ 32, 128 }},
        {{ 48, 128 }},
        {{ 16, 144 }},
        {{ 32, 144 }},
        {{ 48, 144 }},

        {{ 176, 128 }},
        {{ 192, 128 }},
        {{ 208, 128 }},
        {{ 224, 128 }},
        {{ 176, 144 }},
        {{ 192, 144 }},
        {{ 208, 144 }},
        {{ 224, 144 }},

        {{ 16, 176 }},
        {{ 48, 176 }},
        {{ 32, 192 }},
        {{ 64, 192 }},
        {{ 16, 208 }},
        {{ 48, 208 }},
        {{ 32, 224 }},
        {{ 64, 224 }},

        {{ 176, 176 }},
        {{ 208, 176 }},
        {{ 192, 192 }},
        {{ 224, 192 }},
        {{ 176, 208 }},
        {{ 208, 208 }},
        {{ 192, 224 }},
        {{ 224, 224 }},
    }
};

void LoadLevelTextures() {
    _level1_data.texture = LoadTexture("./resources/sprites/level_1.png");
    _level2_data.texture = LoadTexture("./resources/sprites/level_2.png");
}

void UnloadLevelTextures() {
    UnloadTexture(_level1_data.texture);
    UnloadTexture(_level2_data.texture);
}

#endif