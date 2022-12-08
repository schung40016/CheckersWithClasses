#pragma once

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

    void PerformJumpMove(Board& board, std::vector<std::vector<int>>& jumpPieces, Player& enemyPlayer, int turn);

    void PerformRegMove(Board& board, Player& enemyPlayer, int turn);

    void PerformMove(Board& board, const std::vector<std::vector<int>>& moves, const std::vector<int>& newMove, const std::vector<int>& currMove, bool isJump);

    bool FindMove(const std::vector<std::vector<int>>& moveBank, const std::vector<int>& move);

    Piece ExecPlayerMove(Board& board, const std::vector<std::vector<int>>& moves, const std::vector<int>& currMove, bool isJump);

    // Getters & Setters
    int GetPieceCount();

    int GetTurn();

    bool GetIsPlayer();

    void SetTakePiece(int value);
};
