#pragma once
#include <vector>

constexpr int regFirstPiece = 1;
constexpr int regSecPiece = 2;
constexpr int kingFirstPiece = -23;
constexpr int kingSecPiece = -24;


class Piece
{
private:
    int team = 0;
    int type = 0;
    int currPosition = 0;
    std::vector<std::vector<int>> cardinalDir = {{0,0}};

public:
    Piece(int param_type, int param_team, int param_currPos, const std::vector<std::vector<int>>& cardinalDir);

    void Promote(int pieceType);

    const std::vector<int> CalcNewPos(int x, int y, bool checkJump, int boardWidth, int boardLength);

    void ResetPiece(int noTeamNum);

    int Conv2Dto1D(int x, int y);

    bool OutOfBounds(int boardWidth, int boardLength, int x, int y);

    const std::vector<int> GetJumpPos(int boardWidth, int boardLength);

    const std::vector<int> GetMovePos(int boardWidth, int boardLength);

    bool CheckKingPiece(bool isPlayer, int boardWidth, int boardLength);

    //Getters and Setters
    int GetType();

    int GetCurrPosition();

    const std::vector<int> GetConvCurrPos();

    const std::vector<std::vector<int>>& GetCardinalDir();

    int GetTeam();

    void SetTeam(int param_team);

    void SetType(int param_type);

    void SetCurrPosition(int param_currPosition);

    void SetCardinalDir(const std::vector<std::vector<int>>& param_cardinalDir);
};
