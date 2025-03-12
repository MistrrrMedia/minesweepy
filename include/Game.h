#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
    public:
        Game();
        ~Game();
        void initialize();
        void chooseDifficulty();
        void play();
    private:
        Board* board;
        bool uglyLoser; 
        int movesRemaining;
        
};

#endif