#ifndef _LEVEL1_DATA_HPP_
#define _LEVEL1_DATA_HPP_

#include "../../entities/block.hpp"
#include <vector>

std::vector<Block> level1_walls {
    { { 0, 0 }, { 16, 256}, RED },
    { { 16, 0 }, { 224, 16}, RED },
    { { 16, 240 }, { 224, 16}, RED },
    { { 240, 0 }, { 16, 256}, RED },

    { { 16, 64 }, { 80, 16}, RED },
    { { 16, 192 }, { 64, 16}, RED },
    { { 112, 144 }, { 80, 16}, RED },
    { { 160, 96 }, { 80, 16}, RED },
};

#endif