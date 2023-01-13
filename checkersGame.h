#pragma once

#include <queue>
#include "ai.h"
#include "user.h"
#include "player.h"
#include "board.h"

constexpr int turnsForTie = 40;

class CheckersGame {
private:
    std::queue<Player*> turnQueue;
    User *u;
    Ai *a;
    Player* first;
    Player* second;
    Board* board;
    bool noMoves = false;
    int turn = 0;
    int turnTracker = 0;

public: 
    CheckersGame(int playerTurn, int enemyTurn);

    bool Playturn();

    void PrintDraw();

    void PrintWinner();

    bool CheckLosers();

    bool CheckTie();

    bool GetNoMoves();

    void ResetTurnTracker();

    void AddTurnTracker();
};