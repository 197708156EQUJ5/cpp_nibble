#include "nibbles/game.hpp"

#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char *argv[]) {
    std::unique_ptr<nibbles::Game> game = std::make_unique<nibbles::Game>();
    game->initialize();

    while (!game->hasShutDown()) {
    }
    game->stop();

    return 0;
}
