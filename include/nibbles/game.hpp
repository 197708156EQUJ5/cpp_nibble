#pragma once

#include "nibbles/board.hpp"
#include "nibbles/snake.hpp"

#include <chrono>
#include <memory>
#include <thread>

namespace nibbles {

class Game {
public:
    
    Game();
    ~Game() = default;
    Game(const Game &other) = delete;
    Game(Game &other) = delete;
    Game& operator=(const Game &other) = delete;
    Game& operator=(Game &other) = delete;

    void initialize();
    bool hasShutDown();
    void stop();

private:
    
    void create();
    void createColorPairs();
    void keyPressLoop();
    void runControlLoop();
    void showEnd();
    void showTitle();

    bool shutDown;
    std::unique_ptr<Board> board;
    std::unique_ptr<Snake> snake;
    std::unique_ptr<std::thread> keyPressThread;
    std::unique_ptr<std::thread> runThread;

};

} // namespace nibbles
