#pragma once

#include <queue>
#include "ai.h"
#include "user.h"
#include "player.h"
#include "board.h"

class CheckersGame {
private:
    std::queue<Player*> turnQueue;
    User *u;
    Ai *a;
    Player* first;
    Player* second;
    Board* board;
    bool noMoves = false;

public: 
    CheckersGame(int playerTurn, int enemyTurn);

    bool Playturn(int turn);

    void PrintDraw();

    void PrintWinner();

    bool CheckLosers();

    bool CheckTie();

    bool GetNoMoves();
};