#ifndef BOARD_H  // Helps defend program from redefinition compilation errors.
#define BOARD_H

#include <iostream>
#include <vector>
#include "piece.h"

using namespace std;

constexpr int regFirstPiece = 1;
constexpr int regSecPiece = 2;
constexpr int kingFirstPiece = -23;
constexpr int kingSecPiece = -24;
constexpr int noTeam = 32;

class Board {
private:
    vector<vector<Piece>> board;

public: 
    Board(int userTurn, int enemyTurn);

    void drawBoard();
    
    void printBlock(int team, int rowSize, int start, int end, const std::vector<std::vector<int>>& pieceDir);
    
    bool outOfBounds(std::vector<int> param_position);

    bool isJumpPiece(Piece mainPiece, int turn);

    std::vector<std::vector<int>> getJumpPieces(int currentPlayer, int turn);

    std::vector<std::vector<int>> getLegalPieces(int currentPlayer, int turn);

    std::vector<std::vector<int>> getAllMoves(Piece mainPiece, int turn);

    void SwapPieces(int currMoveX, int currMoveY, int newX, int newY);

    void HighlightMove(int x, int y);

    void EraseHighlight(int x, int y);

    void CheckKingPiece(int x, int y, bool isPlayer);

    // Setters and Getters
    vector<vector<Piece>>& getBoard();
};

#endif