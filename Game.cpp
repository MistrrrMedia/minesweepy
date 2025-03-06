#include "Game.h"
#include <iostream>

Game::Game() {

}

void Game::chooseDifficulty() {
    std::cout << "Choose difficulty (#):\n";
    std::cout << "\t1) Beginner (9x9)\n";
    std::cout << "\t2) Intermediate (16x16)\n";
    std::cout << "\t3) Expert (30x16)\n";
    std::cout << "\t4) Custom\n";

    int choice;
    try {
        std::cin >> choice;
    }
    catch(...) {
        std::cout << "Invalid input. Please enter a number.\n";
    }

    ) {

    }
}