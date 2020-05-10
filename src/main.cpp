#include "nibbles/game.hpp"

#include <iostream>
#include <memory>
#include <ctime>

int main(int argc, char *argv[]) {
    srand(time(0));

    std::unique_ptr<nibbles::Game> game = std::make_unique<nibbles::Game>();
    game->initialize();

    while (!game->hasShutDown()) {
    }
    game->stop();

    return 0;
}
