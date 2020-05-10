#pragma once

#include "nibbles/location.hpp"
#include "nibbles/apple.hpp"
#include "nibbles/level.hpp"
#include "nibbles/level_factory.hpp"

#include <cstdint>
#include <vector>

namespace nibbles {

class Board {
public:
    
    Board();
    ~Board() = default;

    void initialize();
    bool hasCollided(Location location);
    bool hasEaten(Location location);
    bool isGameOver();
    uint32_t getSpeed();
    void createLevel(uint32_t levelIndex);
    void decrementLife();
    void incrementScore();
    void update();
    
private:

    void newApple();

    uint32_t score;
    uint32_t lives;
    uint32_t level;
    uint32_t speed;
    std::vector<Location> board;
    Apple apple;
    std::vector<Level> levels;
};
    
}
