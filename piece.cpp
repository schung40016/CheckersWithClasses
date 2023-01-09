#include "piece.h"

Piece::Piece(int param_type, int param_team, int param_currPos, const std::vector<std::vector<int>>& param_cardinalDir)
    : type(param_type), team(param_team), currPosition(param_currPos), cardinalDir(param_cardinalDir)
{
}

void Piece::Promote(int pieceType)
{
    this->type = pieceType;
    this->cardinalDir = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
} 

const std::vector<std::vector<int>> Piece::CalcNewPos(bool checkJump)
{
    std::vector<std::vector<int>> result = {};
    std::vector<int> currPositionConv = GetConvCurrPos();
    int jump = checkJump == true ? 2 : 1;

    for (std::vector<int> pos : cardinalDir)
    {
        int newX = currPositionConv[0] + pos[1] * jump;
        int newY = currPositionConv[1] + pos[0] * jump;
        result.push_back({newX, newY});
    }

    return result;
}

void Piece::ResetPiece(int noTeamNum)
{
    this->type = ' ';
    this->team = noTeamNum;
    this->cardinalDir = {{}};
}

// Setters and Getters.
int Piece::GetType()
{
    return this->type;
}

int Piece::GetCurrPosition()
{
    return this->currPosition; 
}

const std::vector<int> Piece::GetConvCurrPos()
{
    return {this->currPosition / 8, this->currPosition % 8};
}

const std::vector<std::vector<int>>& Piece::GetCardinalDir()
{
    return this->cardinalDir;
}

int Piece::GetTeam()
{
    return this->team;
}

void Piece::SetTeam(int param_team)
{
    this->team = param_team;
}

void Piece::SetType(int param_type)
{
    this->type = param_type;
}

void Piece::SetCurrPosition(int param_currPosition)
{
    this->currPosition = param_currPosition;
}

void Piece::SetCardinalDir(const std::vector<std::vector<int>>& param_cardinalDir)
{
    this->cardinalDir = param_cardinalDir;
}
