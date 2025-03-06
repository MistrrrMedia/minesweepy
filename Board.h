#ifndef BOARD_H
#define BOARD_H

class Board { 
    public:
        char** board;
        Board();
        ~Board();
        bool isMine();
        void move();
        void print();
        int countAdjacentMines();
        void scatterMines();
        void moveMine();
    private:
}

#endif