#include "piece.h"

Piece::Piece(int param_type, int param_team, const std::vector<int>& currPos, const std::vector<std::vector<int>>& cardinalDir)
{
    this->type = param_type;
    this->team = param_team;
    this->currPosition = currPos;
    this->cardinalDir = cardinalDir;
}

// Setters and Getters.
int Piece::getType()
{
    return this->type;
}

const std::vector<int>& Piece::getCurrPosition()
{
    return this->currPosition; 
}

const std::vector<std::vector<int>>& Piece::getCardinalDir()
{
    return this->cardinalDir;
}

int Piece::getTeam()
{
    return this->team;
}

void Piece::setType(int param_type)
{
    this->type = param_type;
}

void Piece::setCurrPosition(const std::vector<int>& param_currPosition)
{
    this->currPosition = param_currPosition;
}
