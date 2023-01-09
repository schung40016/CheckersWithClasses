#pragma once
#include <vector>

class Piece
{
private:
    int team = 0;
    int type = 0;
    int currPosition = 0;
    std::vector<std::vector<int>> cardinalDir = {{0,0}};

public:
    Piece(int param_type, int param_team, int param_currPos, const std::vector<std::vector<int>>& param_cardinalDir);

    void Promote(int pieceType);

    const std::vector<std::vector<int>> CalcNewPos(bool checkJump);

    void ResetPiece(int noTeamNum);

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
