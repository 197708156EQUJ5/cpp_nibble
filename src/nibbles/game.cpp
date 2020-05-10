#include "nibbles/game.hpp"

#include <ncurses.h>
#include <sstream>

namespace nibbles {
    

Game::Game() : 
    shutDown(false), 
    board(nullptr),
    keyPressThread(nullptr), 
    runThread(nullptr) {
}

void Game::initialize() {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    createColorPairs();
    showTitle();

    int input = getch();
    if (input == 'q') {
        this->shutDown = true;
    }
    else if (input == 'c') {
        this->create();
    }
}

void Game::create() {
    this->board = std::make_unique<Board>();
    this->board->initialize();
    this->snake = std::make_unique<Snake>();
    this->snake->initialize();
    if (runThread == nullptr) {
        this->runThread = std::make_unique<std::thread>(&Game::runControlLoop, this);
    }
    if (keyPressThread == nullptr) {
        this->keyPressThread = std::make_unique<std::thread>(&Game::keyPressLoop, this);
    }
}

void Game::createColorPairs() {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
}

void Game::showTitle() {
    attron(COLOR_PAIR(1));
    std::stringstream ss;
    ss << ".__   __.  __  .______   .______    __       _______     _______.";
    mvprintw(15, 10, ss.str().c_str());
    ss.str(std::string());
    ss << "|  \\ |  | |  | |   _  \\  |   _  \\  |  |     |   ____|   /       |";
    mvprintw(16, 10, ss.str().c_str());
    ss.str(std::string());
    ss << "|   \\|  | |  | |  |_)  | |  |_)  | |  |     |  |__     |   (----`";
    mvprintw(17, 10, ss.str().c_str());
    ss.str(std::string());
    ss << "|  . `  | |  | |   _  <  |   _  <  |  |     |   __|     \\   \\    ";
    mvprintw(18, 10, ss.str().c_str());
    ss.str(std::string());
    ss << "|  |\\   | |  | |  |_)  | |  |_)  | |  `----.|  |____.----)   |   ";
    mvprintw(19, 10, ss.str().c_str());
    ss.str(std::string());
    ss << "|__| \\__| |__| |______/  |______/  |_______||_______|_______/";
    mvprintw(20, 10, ss.str().c_str());
    ss.str(std::string());
    attroff(COLOR_PAIR(1));
    
    attron(COLOR_PAIR(2));
    ss << " Use Arrow keys to control the snake";
    mvprintw(22, 10, ss.str().c_str());
    ss.str(std::string());
    ss << " c) continue to the game";
    mvprintw(24, 10, ss.str().c_str());
    ss.str(std::string());
    ss << " q) quit";
    mvprintw(25, 10, ss.str().c_str());
    attroff(COLOR_PAIR(2));
}

void Game::showEnd() {
    attron(COLOR_PAIR(1));
    std::stringstream ss;
    ss << "  _______      ___      .___  ___.  _______      ______   ____    ____  _______ .______      ";
    mvprintw(15, 3, ss.str().c_str());
    ss.str(std::string());
    ss << " /  _____|    /   \\     |   \\/   | |   ____|    /  __  \\  \\   \\  /   / |   ____||   _  \\     ";
    mvprintw(16, 3, ss.str().c_str());
    ss.str(std::string());
    ss << "|  |  __     /  ^  \\    |  \\  /  | |  |__      |  |  |  |  \\   \\/   /  |  |__   |  |_)  |    ";
    mvprintw(17, 3, ss.str().c_str());
    ss.str(std::string());
    ss << "|  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|     |  |  |  |   \\      /   |   __|  |      /     ";
    mvprintw(18, 3, ss.str().c_str());
    ss.str(std::string());
    ss << "|  |__| |  /  _____  \\  |  |  |  | |  |____    |  `--'  |    \\    /    |  |____ |  |\\  \\----.";
    mvprintw(19, 3, ss.str().c_str());
    ss.str(std::string());
    ss << " \\______| /__/     \\__\\ |__|  |__| |_______|    \\______/      \\__/     |_______|| _| `._____|";
    mvprintw(20, 3, ss.str().c_str());
    ss.str(std::string());
    attroff(COLOR_PAIR(2));

}

void Game::keyPressLoop() {
    while (!this->shutDown) {
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                this->snake->changeDirection(Direction::UP);
                break;
            case KEY_DOWN:
                this->snake->changeDirection(Direction::DOWN);
                break;
            case KEY_LEFT:
                this->snake->changeDirection(Direction::WEST);
                break;
            case KEY_RIGHT:
                this->snake->changeDirection(Direction::EAST);
                break;
            case 'q':
                this->shutDown = true;
            default:
                break;
        }
    }
}

void Game::runControlLoop() {
    while (!this->shutDown) {
        this->snake->draw();
        Location head = this->snake->move();
        if (this->snake->hasSelfCollided() || this->board->hasCollided(head)) {
            this->board->decrementLife();
            if (this->board->isGameOver()) {
                this->shutDown = true;
            }
            this->snake->initialize();
        }
        if (this->board->hasEaten(head)) {
            this->board->incrementScore();
        }
        std::stringstream ss;
        ss << this->snake->getSize();
        mvprintw(10, 1, ss.str().c_str());

        std::this_thread::sleep_for(std::chrono::milliseconds(this->board->getSpeed()));
        refresh();
    }
    showEnd();
    refresh();
}

bool Game::hasShutDown() {
    return this->shutDown;    
}

void Game::stop() {
    if (runThread != nullptr) {
        this->runThread->join();
        this->runThread.reset();
    }
    if (keyPressThread != nullptr) {
        this->keyPressThread->join();
        this->keyPressThread.reset();
    }
    echo();
    curs_set(1);
    endwin();

}


} // nibbles
