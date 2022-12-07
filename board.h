#pragma once

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

    void DrawBoard();
    
    void PrintBlock(int team, int rowSize, int start, int end, const std::vector<std::vector<int>>& pieceDir);
    
    bool OutOfBounds(std::vector<int> param_position);

    bool IsJumpPiece(Piece mainPiece, int turn);

    std::vector<std::vector<int>> GetJumpPieces(int currentPlayer, int turn);

    std::vector<std::vector<int>> GetLegalPieces(int currentPlayer, int turn);

    std::vector<std::vector<int>> GetAllMoves(Piece mainPiece, int turn);

    void SwapPieces(int currMoveX, int currMoveY, int newX, int newY);

    void HighlightMove(int x, int y);

    void TakePiece(int x, int y);

    void EraseHighlight(int x, int y);

    void CheckKingPiece(int x, int y, bool isPlayer);

    // Setters and Getters
    vector<vector<Piece>>& GetBoard();
};

