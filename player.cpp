#include "player.h"

Player::Player (int turn, int pieceCount, bool isPlayer)
{
    time(NULL);
    this->turn = turn;
    this->pieceCount = pieceCount;
    this->isPlayer = isPlayer;
}

bool Player::FindMove(const std::vector<int>& moveBank, int move)
{
    for (size_t i{0}; i < moveBank.size(); i++)
    {
        if (moveBank[i] == move)
        {
            return true;
        }
    }

    return false;
}

int Player::GetTurn()
{
    return this->turn;
}

int Player::GetPieceCount()
{
    return this->pieceCount;
}
bool Player::GetIsPlayer()
{
    return this->isPlayer;
}

void Player::SetTakePiece(int value)
{
    this->pieceCount -= value;
}