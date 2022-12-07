#pragma once

#include <vector>

class Piece
{
private:
    int team = 0;
    int type = 0;
    std::vector<int> currPosition = {0,0};
    std::vector<std::vector<int>> cardinalDir = {{0,0}};

public:
    Piece(int param_type, int param_team, const std::vector<int>& param_currPos, const std::vector<std::vector<int>>& cardinalDir);

    void Promote(int pieceType);

    //Getters and Setters
    int GetType();

    const std::vector<int>& GetCurrPosition();

    const std::vector<std::vector<int>>& GetCardinalDir();

    int GetTeam();

    void SetTeam(int param_team);

    void SetType(int param_type);

    void SetCurrPosition(const std::vector<int>& param_currPosition);

    void SetCardinalDir(const std::vector<std::vector<int>>& param_cardinalDir);
};
