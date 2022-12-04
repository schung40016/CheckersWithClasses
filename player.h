#ifndef PLAYER_H  // Helps defend program from redefinition compilation errors.
#define PLAYER_H

#include "board.h"
#include <string>
#include <iostream>
#include <vector>
#include <time.h> 

class Player 
{
private:
    int pieceCount = 12;
    int turn = 0;
    bool isPlayer;

public: 
    Player(int turn, int pieceCount, bool isPlayer);

    void performJumpMove(Board& board, std::vector<std::vector<int>>& jumpPieces, Player enemyPlayer, int turn);

    void performRegMove(Board& board, Player& enemyPlayer, int turn);

    void performMove(Board& board, const std::vector<std::vector<int>>& moves, const std::vector<int>& newMove, const std::vector<int>& currMove, bool isJump);

    bool findMove(const std::vector<std::vector<int>>& moveBank, const std::vector<int>& move);

    Piece execPlayerMove(Board& board, const std::vector<std::vector<int>>& moves, const std::vector<int>& currMove, bool isJump);

    // Getters & Setters
    int getPieceCount();

    int getTurn();

    bool getIsPlayer();

    void setTakePiece();
};

#endif