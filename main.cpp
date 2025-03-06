#include <iostream>
#include "Board.h"
#include "Game.h"

int main(int argc, char* argv[]) {
    // print # of arguments + arguments
    std::cout << "Arguments (" << argc << "): ";
    for(int i = 0; i < argc; ++i) {
        std::cout << argv[i];
        if(i < argc - 1) {
            std::cout << ", ";
        }
        if(i == argc - 1) {
            std::cout << ".";
            std::cout << "\n";
        }
    }

    
}