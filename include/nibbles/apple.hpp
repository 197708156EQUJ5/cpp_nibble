#pragma once

#include <cstdint>
#include <string>

namespace nibbles {

struct Apple {

    void create() {
        x = rand() % 50 + 25;
        y = rand() % 20 + 10;
    }
    
    int y;
    int x;

    const char c = 'O';
};

} // namespace nibbles
