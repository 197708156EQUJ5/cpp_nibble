#pragma once

#include "nibbles/wall.hpp"

#include <vector>

namespace nibbles {

struct Level {
    std::vector<Wall> walls;
};

} // namespace nibbles
