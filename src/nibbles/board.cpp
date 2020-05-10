#include "nibbles/board.hpp"

#include <cstdint>
#include <ncurses.h>

namespace nibbles {

Board::Board() : score(0), lives(3), level(1), speed(300) {
}

void Board::initialize() {
    erase();
    attron(A_BOLD | COLOR_PAIR(3));
    border(ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD);
    attroff(A_BOLD | COLOR_PAIR(3));

    this->update();
    this->levels.push_back(LevelFactory::createLevel1());
    this->levels.push_back(LevelFactory::createLevel2());
    this->createLevel(1);
    this->newApple();

    refresh();
}

void Board::update() {
    attron(A_BOLD | COLOR_PAIR(2));
    mvprintw(1, 20, "Score: %d", score);
    mvprintw(1, 40, "Lives: %d", lives);
    mvprintw(1, 60, "Level: %d", level);
    attroff(A_BOLD | COLOR_PAIR(2));
}

void Board::createLevel(uint32_t levelIndex) {
    this->level = levelIndex + 1;
    update();
    attron(A_BOLD | COLOR_PAIR(4));
    for (uint32_t x = 2; x <= 96; x++) {
        board.push_back(Location{2, x});
    }
    mvaddch(2, 2, ACS_CKBOARD);
    mvhline(2, 3, ACS_CKBOARD, 94);
    mvaddch(2, 96, ACS_CKBOARD);

    for (uint32_t y = 3; y <= 34; y++) {
        board.push_back(Location{y, 2});
        board.push_back(Location{y, 96});
    }

    mvvline(3, 2, ACS_CKBOARD, 34);
    mvvline(3, 96, ACS_CKBOARD, 34);

    for (uint32_t x = 2; x <= 96; x++) {
        board.push_back(Location{36, x});
    }
    mvaddch(36, 2, ACS_CKBOARD);
    mvhline(36, 3, ACS_CKBOARD, 94);
    mvaddch(36, 96, ACS_CKBOARD);
    attroff(A_BOLD | COLOR_PAIR(4));

    attron(A_BOLD | COLOR_PAIR(5));
    std::vector<Wall> walls = this->levels.at(levelIndex).walls;
    for (Wall wall : walls) {
        if (wall.isVertical) {
            mvvline(wall.startingPoint.y, wall.startingPoint.x, ACS_CKBOARD, wall.length);
        } else {
            mvhline(wall.startingPoint.y, wall.startingPoint.x, ACS_CKBOARD, wall.length);
        }
    }
    attroff(A_BOLD | COLOR_PAIR(5));
}

uint32_t Board::getSpeed() {
    return speed;
}

void Board::decrementLife() {
    this->lives--;
    update();
}

void Board::incrementScore() {
    this->score++;
    this->newApple();
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

bool Board::hasEaten(Location location) {
    if (apple.y == (int)location.y && apple.x == (int)location.x) {
        return true;
    }

    return false;
}

void Board::newApple() {
    this->apple.create();
    mvaddch(this->apple.y, this->apple.x, this->apple.c);
    refresh();
}

bool Board::isGameOver() {
    return this->lives == 0;
}

}
