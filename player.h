#pragma once

#include "board.h"
#include <string>
#include <iostream>
#include <vector>
#include <time.h> 

class Player 
{
protected:
    int pieceCount = 12;
    int turn = 0;
    bool isPlayer;

public: 
    Player(int turn, int pieceCount, bool isPlayer);

    virtual void PerformJumpMove(Board& board, std::vector<int>& jumpPieces, Player& enemyPlayer, int turn) {};

    virtual void PerformRegMove(Board& board, Player& enemyPlayer, int turn) {};

    virtual void PerformMove(Board& board, const std::vector<int>& moves, int newMove, int currMove, bool isJump) {};

    bool FindMove(const std::vector<int>& moveBank, int move);

    // Getters & Setters
    int GetPieceCount();

    int GetTurn();

    bool GetIsPlayer();

    void SetTakePiece(int value);
};
