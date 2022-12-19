#pragma once

#include "player.h"

class Ai : public Player 
{
public:
    Ai(int turn, int pieceCount, bool isPlayer);

    void PerformJumpMove(Board& board, std::vector<int>& jumpPieces, Player& enemyPlayer, int turn);

    void PerformRegMove(Board& board, Player& enemyPlayer, int turn);

    void PerformMove(Board& board, const std::vector<int>& moves, int newMove, int currMove, bool isJump);
};