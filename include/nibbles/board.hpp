#pragma once

#include "nibbles/location.hpp"
#include "nibbles/apple.hpp"

#include <cstdint>
#include <vector>

namespace nibbles {

class Board {
public:
    
    Board();
    ~Board() = default;
    Board(const Board &other) = delete;
    Board(Board &other) = delete;
    Board& operator=(const Board &other) = delete;
    Board& operator=(Board &other) = delete;

    void initialize();
    bool hasCollided(Location location);
    bool hasEaten(Location location);
    bool isGameOver();
    uint32_t getSpeed();
    void createLevel();
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
};
    
}
