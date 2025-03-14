#include "../include/Game.h"
#include <iostream>

Game::Game() {
    movesRemaining = 0;
    board = nullptr;
    uglyLoser = false;
}

Game::~Game() {
    // destructor
    delete board;
}

void Game::chooseDifficulty() {
    std::cout << "Choose difficulty (#):\n";
    std::cout << "\t1) Beginner (9x9 10 mines)\n";
    std::cout << "\t2) Intermediate (16x16 40 mines)\n";
    std::cout << "\t3) Expert (30x16 99 mines)\n";
    std::cout << "\t4) Custom\n";
    std::cout << "Choice: ";

    int choice = 0;
    std::cin >> choice;
    while(std::cin.fail()) // input validation 
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter a number: \n";
		std::cin >> choice;
	}

    int sizeX, sizeY, mineCount = 0;
    switch(choice) {
        case 1: // beginner
            sizeX = 9;
            sizeY = 9;
            mineCount = 10;
            break;
        
        case 2: // intermediate
            sizeX = 16;
            sizeY = 16;
            mineCount = 40;
            break;

        case 3: // expert
            sizeX = 30;
            sizeY = 16;
            mineCount = 99;
            break;

        case 4: // custom board size
            // choose x
            std::cout << "Enter your desired board width (Minimum: 3): ";
            std::cin >> sizeX;
            // input validation
            while(std::cin.fail() || sizeX < 3) 
            {
                // if input it not a number
                if(std::cin.fail()) { 
                    std::cout << "Invalid input. Please enter a number: ";
                }
                // if input is less than 3
                else { 
                    std::cout << "Invalid input. Please enter a number that is at least 3: ";
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> sizeX;
            }

            // then choose y
            std::cout << "Enter your desired board height (Minimum: 3): ";
            std::cin >> sizeY;
            // input validation
            while(std::cin.fail() || sizeY < 3)  
            {
                // if input it not a number
                if(std::cin.fail()) { 
                    std::cout << "Invalid input. Please enter a number: ";
                }
                // if input is less than 3
                else {
                    std::cout << "Invalid input. Please enter a number that is at least 3: ";
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> sizeY;
            }

            // then choose mine count
            std::cout << "Enter your desired mine count (Minimum: 1, Maximum: " << sizeX * sizeY - 1 << "): ";
            std::cin >> mineCount;
            while(std::cin.fail() || mineCount < 1 || mineCount >= sizeX * sizeY) // input validation 
            {
                // if input it not a number
                if(std::cin.fail()) { 
                    std::cout << "Invalid input. Please enter a number: ";
                }
                // if input is less than 1
                else if(mineCount < 1) { 
                    std::cout << "Invalid input. Please enter a number greater than 0: ";
                }
                // if input is greater than or equal to the total number of cells
                else { 
                    std::cout << "Invalid input. Please enter a number less than " << sizeX * sizeY << ": ";
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> mineCount;
            }

            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            // board will remain nullptr, loop back to the beginning (if in initialize())
            return; 
    }
    std::cout << '\n';
    // only creates a new board if the user input has been valid up to this point
    board = new Board(sizeX, sizeY, mineCount);
    movesRemaining = sizeX * sizeY - mineCount;
}

void Game::play() {
    bool gammeInProgress = true;
    while(gammeInProgress && movesRemaining > 0) {
        board->printView();
        int x, y = 0;
        std::cout << "Enter x coordinate: ";
        std::cin >> x;
        while(std::cin.fail() || x < 0 || x >= board->getSizeX()) // input validation 
        {
            // if input it not a number
            if(std::cin.fail()) { 
                std::cout << "Invalid input. Please enter a number: ";
            }
            // if input is less than 0
            else if(x < 0) { 
                std::cout << "Invalid input. Please enter a number that is at least 0: ";
            }
            // if input is greater than or equal to the width of the board
            else { 
                std::cout << "Invalid input. Please enter a number less than " << board->getSizeX() << ": ";
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> x;
        }

        std::cout <<"Enter y coordinate: ";
        std::cin >> y;
        while(std::cin.fail() || y < 0 || y >= board->getSizeY()) // input validation 
        {
            // if input it not a number
            if(std::cin.fail()) { 
                std::cout << "Invalid input. Please enter a number: ";
            }
            // if input is less than 0
            else if(y < 0) { 
                std::cout << "Invalid input. Please enter a number that is at least 0: ";
            }
            // if input is greater than or equal to the width of the board
            else { 
                std::cout << "Invalid input. Please enter a number less than " << board->getSizeY() << ": ";
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> y;
        }
        std::cout << '\n';

        gammeInProgress = board->sweep(x, y, uglyLoser, movesRemaining);
    }
    // if you are an ugly loser and you lost by choosing a mine
    if(uglyLoser) {
        std::cout << "You are an ugly loser.\n\n";
        board->explode();
    }
    else {
        std::cout << "You are a not a loser.\n\n";
    }
    board->printView();
}

void Game::initialize() {
    do{ // loop until user chooses a valid difficulty
        chooseDifficulty();
    }
    while(board == nullptr); 
}

