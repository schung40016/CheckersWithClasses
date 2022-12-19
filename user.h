#pragma once

#include "player.h"

class User : public Player 
{
public: 
    User(int turn, int pieceCount, bool isPlayer);

    void PerformJumpMove(Board& board, std::vector<int>& jumpPieces, Player& enemyPlayer, int turn);

    void PerformRegMove(Board& board, Player& enemyPlayer, int turn);

    void PerformMove(Board& board, const std::vector<int>& moves, int newMove, int currMove, bool isJump);

    Piece ExecPlayerMove(Board& board, const std::vector<int>& moves, const int currMove, bool isJump);
};