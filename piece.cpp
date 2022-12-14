#include "piece.h"

Piece::Piece(int param_type, int param_team, int currPos, const std::vector<std::vector<int>>& cardinalDir)
{
    this->type = param_type;
    this->team = param_team;
    this->currPosition = currPos;
    this->cardinalDir = cardinalDir;
}

void Piece::Promote(int pieceType)
{
    this->type = pieceType;
    this->cardinalDir = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
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
