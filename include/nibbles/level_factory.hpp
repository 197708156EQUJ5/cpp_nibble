#pragma once

#include "nibbles/location.hpp"
#include "nibbles/apple.hpp"
#include "nibbles/level.hpp"

#include <cstdint>
#include <vector>

namespace nibbles {

class LevelFactory {
public:
    static Level createLevel1();
    static Level createLevel2();
    static Level createLevel3();
    static Level createLevel4();
};

} // namespace nibbles

