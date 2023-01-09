#include "player.h"

Player::Player (int param_turn, int param_pieceCount, bool param_isPlayer)
    : turn(param_turn), pieceCount(param_pieceCount), isPlayer(param_isPlayer)
{
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