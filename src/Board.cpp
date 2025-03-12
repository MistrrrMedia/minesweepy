#include "../include/Board.h"
#include <iostream>
#include <cmath>
// #include <random>

bool Board::sweep(int x, int y, bool &lose, int &movesRemaining) {
    // base case: empty or numbered cell
    if(viewGrid[y][x] != '#') {
        return true;
    }

    movesRemaining--;
    // if there isn't a mine
    if(!mineGrid[y][x]) {
        // #1 count adjacent mines
        // 
        // hol on i gotta think rq
        // remember the format is [y][x]
        // [-1][-1]  [-1][0]  [-1][1] 
        // [0] [-1]  [0] [0]  [0] [1] 
        // [1] [-1]  [1] [0]  [1] [1]
        // exclude [0][0] = [y][x], avoid redundancy
        int yPos[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int xPos[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int adjacentMineCount = 0;
        for(int i = 0; i < 8; ++i) {
            // if the adjacent cell is within bounds
            if(y + yPos[i] < sizeY 
                && y + yPos[i] >= 0
                && x + xPos[i] < sizeX 
                && x + xPos[i] >= 0) {
                // if there is a mine in this adjacent cell
                if(mineGrid[y + yPos[i]][x + xPos[i]]) {
                    adjacentMineCount++;
                }
            }
        }

        // replace chosen cell with adjacentMineCount
        if(adjacentMineCount > 0) {
            viewGrid[y][x] = '0' + adjacentMineCount;
        }
        // if there are no adjacent mines, recursively make
        // moves for the user on surrounding cells
        else {
            viewGrid[y][x] = ' ';

            bool sweeped = true;
            for(int i = 0; i < 8; ++i) {
                // if the adjacent cell is within bounds
                if(y + yPos[i] < sizeY 
                    && y + yPos[i] >= 0
                    && x + xPos[i] < sizeX 
                    && x + xPos[i] >= 0) {
                    // if there isn't a mine in this adjacent cell
                    if(!mineGrid[y + yPos[i]][x + xPos[i]]) {
                        sweeped = sweep(x + xPos[i], y + yPos[i], lose, movesRemaining);
                    }
                }
            }

            return sweeped;
        }

        return true;
    }

    // if the user clicks on a mine
    else { 
        lose = true;
        return false; 
    }
}

Board::Board(int x, int y, int amtMines) {
    sizeX = x;
    sizeY = y;

    viewGrid = new char*[sizeY];
    mineGrid = new bool*[sizeY];
    for(int i = 0; i < sizeY; ++i) {
        viewGrid[i] = new char[sizeX];
        mineGrid[i] = new bool[sizeX];
        // populate viewGrid with '#'
        // and populate mineGrid with zero mines. 
        for (int j = 0; j < sizeX; ++j) {
            viewGrid[i][j] = '#';
            mineGrid[i][j] = false;
        }
    }

    srand(time(0));
    for(int i = 0; i < amtMines; ++i) {
        int xRand = rand() % (sizeX - 1);
        int yRand = rand() % (sizeY - 1);
        while(mineGrid[yRand][xRand]) {
            xRand = rand() % sizeX;
        }
        mineGrid[yRand][xRand] = true;
    }
}

Board::~Board() {
    for(int i = 0; i < sizeY; ++i) {
        delete[] viewGrid[i];
        delete[] mineGrid[i];
    }

    delete[] viewGrid;
    delete[] mineGrid;
}

int Board::getSizeX() {
    return sizeX;
}

int Board::getSizeY() {
    return sizeY;
}

void Board::printView() {
    // print the x-axis numbers
    std::cout << "\t";
    for(int i = 0; i < sizeX; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n\n";

    for(int i = 0; i < sizeY; ++i) {
        // print the y-axis numbers
        std::cout << i << "\t";
        // print the viewGrid
        for(int j = 0; j < sizeX; ++j) {
            std::cout << viewGrid[i][j] << ' ';
        }
        std::cout << "\n\n";
    }
}

void Board::explode() {
    // print the x-axis numbers
    for(int i = 0; i < sizeY; i++) {
        for(int j = 0; j < sizeX; ++j) {
            // if there is a mine, replace the character with a @
            if(mineGrid[i][j]) {
                viewGrid[i][j] = '@';
            }
        }
    }
}
