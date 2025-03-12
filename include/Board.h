#ifndef BOARD_H
#define BOARD_H

class Board { 
    public:
        Board(int x, int y, int amtMines);
        ~Board();
        bool sweep(int x, int y, bool &lose, int &movesRemaining);
        int getSizeX();
        int getSizeY();
        void printView();
        void explode();
    private:
        int sizeX, sizeY;
        int amtMines;
        char** viewGrid;
        bool** mineGrid;

};

#endif