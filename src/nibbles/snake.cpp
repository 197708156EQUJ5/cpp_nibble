#include "nibbles/snake.hpp"

#include <iterator>
#include <ncurses.h>
#include <sstream>

namespace nibbles {

Snake::Snake() : snakeLength(5), startLocation(20), direction(Direction::UP) {
}

void Snake::initialize() {
    for (Location location : this->body) {
        mvaddch(location.y, location.x, ' ');
    }
    this->body.clear();
    for (uint32_t y = startLocation; y < startLocation + snakeLength; y++) {
        this->body.push_back({y, 50});
    }
}

void Snake::draw() {
    for (uint32_t i = 0; i < this->body.size(); i++) {
        Location location = this->body[i];
        if (i == 0) {
            attron(A_BOLD | COLOR_PAIR(1));
            mvaddch(location.y, location.x, ACS_DIAMOND);
            attroff(A_BOLD | COLOR_PAIR(1));
        } else {
            attron(A_BOLD | COLOR_PAIR(2));
            mvaddch(location.y, location.x, ACS_CKBOARD);
            attroff(A_BOLD | COLOR_PAIR(2));
        }
    }
}

Location Snake::move() {
    Location removedCell = this->body.at(this->body.size() - 1);
    mvaddch(removedCell.y, removedCell.x, ' ');
    this->body.pop_back();
    Location prev_head = this->body.at(0);
    Location head;
    switch (this->direction) {
        case Direction::UP:
            head = Location{prev_head.y - 1, prev_head.x};
            break;
        case Direction::DOWN:
            head = Location{prev_head.y + 1, prev_head.x};
            break;
        case Direction::WEST:
            head = Location{prev_head.y, prev_head.x - 1};
            break;
        case Direction::EAST:
            head = Location{prev_head.y, prev_head.x + 1};
            break;
        default:
            break;
    }
    this->body.insert(this->body.begin(), head);

    return head;
}

void Snake::changeDirection(Direction direction) {
    this->direction = direction;
}

bool Snake::hasSelfCollided() {
    Location head = this->body.at(0);
    std::vector<Location>::iterator it = this->body.begin();
    std::advance(it, 1);
    int i = 17;
    while (it != this->body.end()) {
        Location location = *it;
        if (head.y == location.y && head.x == location.x) {
            return true;
        }
        it++;
        i++;
    }

    return false;
}

uint32_t Snake::getSize() {
    return this->body.size();
}

}
