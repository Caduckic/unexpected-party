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
        {{ 128, 128 }, CoinMode::DEFAULT},
        {{ 144, 128 }, CoinMode::DEFAULT},
        {{ 160, 128 }, CoinMode::DEFAULT},

        {{ 16, 160 }, CoinMode::DEFAULT},
        {{ 32, 160 }, CoinMode::DEFAULT},
        {{ 48, 160 }, CoinMode::DEFAULT},
        {{ 16, 176 }, CoinMode::DEFAULT},
        {{ 32, 176 }, CoinMode::DEFAULT},
        {{ 48, 176 }, CoinMode::DEFAULT},

        {{ 160, 192 }, CoinMode::DEFAULT},
        {{ 176, 192 }, CoinMode::DEFAULT},
        {{ 192, 192 }, CoinMode::DEFAULT},
        {{ 208, 192 }, CoinMode::DEFAULT},
        {{ 224, 192 }, CoinMode::DEFAULT},
        {{ 160, 208 }, CoinMode::DEFAULT},
        {{ 176, 208 }, CoinMode::DEFAULT},
        {{ 192, 208 }, CoinMode::DEFAULT},
        {{ 208, 208 }, CoinMode::DEFAULT},
        {{ 224, 208 }, CoinMode::DEFAULT},
        {{ 160, 224 }, CoinMode::DEFAULT},
        {{ 176, 224 }, CoinMode::DEFAULT},
        {{ 192, 224 }, CoinMode::DEFAULT},
        {{ 208, 224 }, CoinMode::DEFAULT},
        {{ 224, 224 }, CoinMode::DEFAULT}
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
        {{ 112, 32 }, CoinMode::DEFAULT},
        {{ 112, 48 }, CoinMode::DEFAULT},

        {{ 208, 96 }, CoinMode::DEFAULT},

        {{ 16, 112 }, CoinMode::DEFAULT},
        {{ 32, 112 }, CoinMode::DEFAULT},
        {{ 48, 112 }, CoinMode::DEFAULT},
        {{ 16, 128 }, CoinMode::DEFAULT},
        {{ 32, 128 }, CoinMode::DEFAULT},
        {{ 48, 128 }, CoinMode::DEFAULT},
        {{ 16, 144 }, CoinMode::DEFAULT},
        {{ 32, 144 }, CoinMode::DEFAULT},
        {{ 48, 144 }, CoinMode::DEFAULT},

        {{ 176, 128 }, CoinMode::DEFAULT},
        {{ 192, 128 }, CoinMode::DEFAULT},
        {{ 208, 128 }, CoinMode::DEFAULT},
        {{ 224, 128 }, CoinMode::DEFAULT},
        {{ 176, 144 }, CoinMode::DEFAULT},
        {{ 192, 144 }, CoinMode::DEFAULT},
        {{ 208, 144 }, CoinMode::DEFAULT},
        {{ 224, 144 }, CoinMode::DEFAULT},

        {{ 16, 176 }, CoinMode::DEFAULT},
        {{ 48, 176 }, CoinMode::DEFAULT},
        {{ 32, 192 }, CoinMode::DEFAULT},
        {{ 64, 192 }, CoinMode::DEFAULT},
        {{ 16, 208 }, CoinMode::DEFAULT},
        {{ 48, 208 }, CoinMode::DEFAULT},
        {{ 32, 224 }, CoinMode::DEFAULT},
        {{ 64, 224 }, CoinMode::DEFAULT},

        {{ 176, 176 }, CoinMode::DEFAULT},
        {{ 208, 176 }, CoinMode::DEFAULT},
        {{ 192, 192 }, CoinMode::DEFAULT},
        {{ 224, 192 }, CoinMode::DEFAULT},
        {{ 176, 208 }, CoinMode::DEFAULT},
        {{ 208, 208 }, CoinMode::DEFAULT},
        {{ 192, 224 }, CoinMode::DEFAULT},
        {{ 224, 224 }, CoinMode::DEFAULT},
    }
};

LevelData _level3_data = {
    {},
    {
        { { 0, 0 }, { 16, 256 } },
        { { 16, 0 }, { 224, 16 } },
        { { 16, 240 }, { 224, 16 } },
        { { 240, 0 }, { 16, 256 } },

        { { 80, 16 }, { 16, 16 } },
        { { 176, 16 }, { 16, 80 } },

        { { 80, 48 }, { 16, 112 } },

        { { 176, 112 }, { 16, 80 } },

        { { 80, 176 }, { 16, 64 } },

        { { 176, 208 }, { 16, 32 } },

        
        { { 224, 48 }, { 16, 16 } },

        { { 64, 80 }, { 16, 16 } },

        { { 96, 96 }, { 32, 16 } },

        { { 192, 112 }, { 16, 16 } },

        { { 16, 128 }, { 16, 16} },

        { { 144, 144 }, { 32, 16 } },

        { { 224, 160 }, { 16, 16 } },

        { { 64, 176 }, { 16, 16 } },

        { { 16, 192 }, { 16, 16 } },

        { { 96, 192 }, { 32, 16 } },

        { { 192, 208 }, { 16, 16 } },
        //{ { 16, 128 }, { 16, 16} },
    },
    {
        {{ 224, 224 }, CoinMode::DEFAULT},//temp
    }
};

LevelData _level4_data = {
    {},
    {
        { { 0, 0 }, { 16, 256 } },
        { { 16, 0 }, { 224, 16 } },
        { { 16, 240 }, { 224, 16 } },
        { { 240, 0 }, { 16, 256 } },

        { { 16, 64 }, { 48, 64 } },
        { { 176, 64 }, { 64, 32 } },
        { { 144, 80 }, { 32, 16 } },
        { { 64, 112 }, { 32, 16 } },
        { { 176, 128 }, { 64, 32 } },
        { { 96, 160 }, { 48, 32 } },
        { { 16, 192 }, { 48, 48 } },
    },
    {
        {{ 224, 224 }, CoinMode::DEFAULT},//temp
    }
};

void LoadLevelTextures() {
    _level1_data.texture = LoadTexture("./resources/sprites/level_1.png");
    _level2_data.texture = LoadTexture("./resources/sprites/level_2.png");
    _level3_data.texture = LoadTexture("./resources/sprites/level_3.png");
    _level4_data.texture = LoadTexture("./resources/sprites/level_4.png");
}

void UnloadLevelTextures() {
    UnloadTexture(_level1_data.texture);
    UnloadTexture(_level2_data.texture);
    UnloadTexture(_level3_data.texture);
    UnloadTexture(_level4_data.texture);
}

#endif