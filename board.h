#pragma once

#include <iostream>
#include <vector>
#include "piece.h"

constexpr int noTeam = 32;
constexpr int notValidPos = -1;

class Board {
private:
    std::vector<Piece> board;
    int boardLength = 8;
    int boardWidth = 8;

public: 
    Board(int userTurn, int enemyTurn);

    void DrawBoard();
    
    void PrintBlock(int team, int rowSize, int start, int end, const std::vector<std::vector<int>>& pieceDir);
    
    bool OutOfBounds(std::vector<int> param_position);

    bool IsJumpPiece(Piece mainPiece, int turn);

    std::vector<int> GetJumpPieces(int currentPlayer, int turn);

    std::vector<int> GetLegalPieces(int currentPlayer, int turn);

    std::vector<int> GetAllMoves(Piece mainPiece, int turn);

    void SwapPieces(int currMove, int newMove);

    void HighlightMove(int currPos);

    void TakePiece(int currPos);

    void EraseHighlight(int currPos);

    int Conv2Dto1D(int x, int y);

    // Setters and Getters
    std::vector<Piece>& GetBoard();

    int GetBoardLength();

    int GetBoardWidth();
};

