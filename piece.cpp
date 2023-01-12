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

const std::vector<int> Piece::CalcNewPos(int x, int y, bool checkJump, int boardWidth, int boardLength)
{
    std::vector<int> result = {};
    std::vector<int> currPositionConv = GetConvCurrPos();
    int jump = checkJump == true ? 2 : 1;

    for (std::vector<int> pos : cardinalDir)
    {
        int newX = currPositionConv[0] + pos[1] * jump;
        int newY = currPositionConv[1] + pos[0] * jump;

        if (!OutOfBounds(boardWidth, boardLength, newX, newY))
        {
            result.push_back(Conv2Dto1D(newX, newY));
        }
        else
        {
            // Invalid move, mark it.
            result.push_back(-1);
        }
    }

    return result;
}

void Piece::ResetPiece(int noTeamNum)
{
    this->type = ' ';
    this->team = noTeamNum;
    this->cardinalDir = {{}};
}

int Piece::Conv2Dto1D(int x, int y)
{
    return ((x * 8) + y);
}

bool Piece::OutOfBounds(int boardWidth, int boardLength, int x, int y)
{
    // If X and Y are within the bounds
    if (!(x >= 0 && x < boardWidth) || !(y >= 0 && y < boardLength))
    {
        return true;
    }
    return false;
}

const std::vector<int> Piece::GetJumpPos(int boardWidth, int boardLength)
{
    return CalcNewPos(currPosition / boardLength, currPosition % boardWidth, true, boardWidth, boardLength);
}

const std::vector<int> Piece::GetMovePos(int boardWidth, int boardLength)
{
    return CalcNewPos(currPosition / boardLength, currPosition % boardWidth, false, boardWidth, boardLength);
}

bool Piece::CheckKingPiece(bool isPlayer, int boardWidth, int boardLength)
{
    // Any super pieces to transform?
    if (type == regFirstPiece || type == regSecPiece)
    {
        if (((currPosition / boardLength == 7) && isPlayer) || (((currPosition / boardLength == 0)) && !isPlayer))
        {
            type == regFirstPiece ? this->Promote(kingFirstPiece) : this->Promote(kingSecPiece);
            
            // Player gained advantage, reset turn tracker.
            return true;
        }
    }

    return false;
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
