#include "nibbles/board.hpp"

#include <cstdint>
#include <ncurses.h>

namespace nibbles {

Board::Board() : score(0), lives(3), level(1), speed(100) {
}

void Board::initialize() {
    erase();
    attron(A_BOLD | COLOR_PAIR(3));
    border('|', '|', '-', '-', '+', '+', '+', '+');
    attroff(A_BOLD | COLOR_PAIR(3));

    this->update();
    this->create();

    refresh();
}

void Board::update() {
    attron(A_BOLD | COLOR_PAIR(2));
    mvprintw(1, 20, "Score: %d", score);
    mvprintw(1, 40, "Lives: %d", lives);
    mvprintw(1, 60, "Level: %d", level);
    attroff(A_BOLD | COLOR_PAIR(2));
}

void Board::create() {
    for (uint32_t x = 2; x <= 96; x++) {
        board.push_back(Location{2, x});
    }
    mvaddch(2, 2, '+');
    mvhline(2, 3, '-', 94);
    mvaddch(2, 96, '+');

    for (uint32_t y = 3; y <= 34; y++) {
        board.push_back(Location{y, 2});
        board.push_back(Location{y, 96});
    }

    mvvline(3, 2, '|', 34);
    mvvline(3, 96, '|', 34);

    for (uint32_t x = 2; x <= 96; x++) {
        board.push_back(Location{36, x});
    }
    mvaddch(36, 2, '+');
    mvhline(36, 3, '-', 94);
    mvaddch(36, 96, '+');
}

uint32_t Board::getSpeed() {
    return speed;
}

void Board::decrementLife() {
    this->lives--;
    update();
}

bool Board::hasCollided(Location location) {
    for (Location loc : this->board) {
        if (loc.y == location.y && loc.x == location.x) {
            return true;
        }
    }

    return false;
}

bool Board::isGameOver() {
    return this->lives == 0;
}

}
