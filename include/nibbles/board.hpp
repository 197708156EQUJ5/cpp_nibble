#pragma once

#include "nibbles/location.hpp"

#include <cstdint>
#include <vector>

namespace nibbles {

class Board {
public:
    
    Board();
    ~Board() = default;

    void initialize();
    void create();
    void update();
    uint32_t getSpeed();
    void decrementLife();
    bool hasCollided(Location location);
    bool isGameOver();
    
private:

    uint32_t score;
    uint32_t lives;
    uint32_t level;
    uint32_t speed;
    std::vector<Location> board;
    
};
    
}
