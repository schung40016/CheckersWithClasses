#include "checkersGame.h"

CheckersGame::CheckersGame(int playerTurn, int enemyTurn)
{
    User user(playerTurn, 12, true);
    Ai enemy(enemyTurn, 12, false);
    
    u = new User(playerTurn, 12, true);
    a = new Ai(enemyTurn, 12, false);

    if (playerTurn == 0)
    {
        turnQueue.push(u);
        turnQueue.push(a);
    }
    else
    {
        turnQueue.push(a);
        turnQueue.push(u);
    }

    board = new Board(user.GetTurn(), enemy.GetTurn());
}

bool CheckersGame::Playturn()
{
    first = turnQueue.front();
    turnQueue.pop();
    second = turnQueue.front();

    if (board->GetLegalPieces(first->GetTurn(), turn).size() == 0 && board->GetLegalPieces(second->GetTurn() , turn).size() == 0)
    {
        noMoves = true;
        return true;
    }

    if (board->GetLegalPieces(first->GetTurn(), turn).size() == 0)
    {
        first->SetTakePiece(first->GetPieceCount());
        return true;
    }

    if (board->GetLegalPieces(second->GetTurn(), turn).size() == 0)
    {
        second->SetTakePiece(second->GetPieceCount());
        return true;
    }

    board->DrawBoard();
    std::vector<int> jumpPieces;

    std::cout << "Turn Tracker: " << turnTracker << "." << std::endl;
    std::cout << "First player: " << first->GetIsPlayer() << "." << std::endl;

    jumpPieces = board->GetJumpPieces(first->GetTurn(), turn);

    if (jumpPieces.size() > 0)
    {
        first->PerformJumpMove(*board, jumpPieces, *second, turn);

        // Piece taken. One player gained advantage.
        turnTracker = 0;
    }
    else
    {
        bool gainAdvantage = first->PerformRegMove(*board, *second, turn);
        
        if (gainAdvantage)
        {
            turnTracker = 0;
        }
        else
        {
            ++turnTracker;
        }
    }

    ++turn;

    turnQueue.push(first);

    if (this->CheckTie())
    {
        return true;
    }

    return false;
}

void CheckersGame::PrintDraw()
{
    std::cout << "Game ended in a draw! Due to one of these circumstances - " << std::endl;
    std::cout << "No move rule: neither side could make a move." << std::endl;
    std::cout << "40 turn rule: neither side gained an advantage for 40 consecutive turns, thus the game is a draw" << std::endl;
}

void CheckersGame::PrintWinner()
{
    std::cout << typeid(*first).name() << " won with " << first->GetPieceCount() << " pieces on the board." << std::endl;
    std::cout << typeid(*second).name() << " lost!" << std::endl;
}

bool CheckersGame::CheckLosers()
{
    bool loser = (u->GetPieceCount() != 0 && a->GetPieceCount() != 0);   
    return loser;
}

bool CheckersGame::CheckTie()
{
    if (turnTracker == turnsForTie)
    {
        return true;
    }

    return false;
}

bool CheckersGame::GetNoMoves()
{
    return this->noMoves;
}
