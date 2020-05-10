#pragma once

#include "nibbles/location.hpp"

#include <vector>
#include <cstdint>

namespace nibbles {

enum class Direction {
    UP,
    DOWN,
    WEST,
    EAST
};

class Snake {
public:

    Snake();
    ~Snake() = default;
    
    void initialize();
    void draw();
    Location move();
    void changeDirection(Direction direction);
    uint32_t getSize();
    bool hasSelfCollided();
    
private:
    
    uint32_t snakeLength;
    uint32_t startLocation;
    Direction direction;
    std::vector<Location> body;
};
} // namespace nibbles
