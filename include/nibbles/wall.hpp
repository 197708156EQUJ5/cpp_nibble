#pragma once

#include "nibbles/location.hpp"

#include <cstdint>

namespace nibbles {

struct Wall {
    Location startingPoint;
    uint32_t length;
    bool isVertical;
};

} // namespace nibbles
