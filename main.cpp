#include "piece.h"
#include "board.h"
#include "player.h"
#include "ai.h"
#include "user.h"
#include <queue>

/*
Goals: 
- Create game class and move all main loop code items into game class.
- Refactor some of the calculation code into piece class. 
*/  


int main()
{
    int enemyTurn = 0;
    int turn = 0;

    int response = 0;

    std::cout << "\n\nWelcome to the game of checkers using classes!" << std::endl;
    std::cout << "Would you like to play? Press 1 for yes or anything else for no" << std::endl;
    std::cin >> response;

    if (response != 1)
    {
        std::cout << "Goodbye!";
        return 0;
    }

    std::cout << "Before the game starts, would you like to go first or last? Type 1 for last and 0 for first." << std::endl;
    std::cin >> response;

    response == 0 ? enemyTurn = 1 : enemyTurn = 0;

    std::queue<Player*> turnQueue;
    User user(response, 12, true);
    Ai enemy(enemyTurn, 12, false);

    User *u;
    Ai *a;
    u = new User(response, 12, true);
    a = new Ai(enemyTurn, 12, false);

    if (response == 0)
    {
        turnQueue.push(u);
        turnQueue.push(a);
    }
    else
    {
        turnQueue.push(a);
        turnQueue.push(u);
    }

    Board board(user.GetTurn(), enemy.GetTurn());

    bool noMoves = false;

    Player* first;
    Player* second;

    // Game Loop.
    while (user.GetPieceCount() != 0 && enemy.GetPieceCount() != 0)
    {
        first = turnQueue.front();
        turnQueue.pop();
        second = turnQueue.front();

        if (board.GetLegalPieces(first->GetTurn(), turn).size() == 0 && board.GetLegalPieces(second->GetTurn() , turn).size() == 0)
        {
            noMoves = true;
            break;
        }

        if (board.GetLegalPieces(first->GetTurn(), turn).size() == 0)
        {
            first->SetTakePiece(first->GetPieceCount());
            break;
        }

        if (board.GetLegalPieces(second->GetTurn(), turn).size() == 0)
        {
            second->SetTakePiece(second->GetPieceCount());
            break;
        }

        board.DrawBoard();
        std::vector<int> jumpPieces;

        std::cout << "Turn Tracker: " << board.GetTurnTracker() << "." << std::endl;
        std::cout << "First player: " << first->GetIsPlayer() << "." << std::endl;

        jumpPieces = board.GetJumpPieces(first->GetTurn(), turn);

        if (jumpPieces.size() > 0)
        {
            first->PerformJumpMove(board, jumpPieces, *second, turn);
        }
        else
        {
            first->PerformRegMove(board, *second, turn);
        }

        turnQueue.push(first);

        turn++;

        if (board.CheckTie())
        {
            break;
        }
    }

    if (board.CheckTie() || noMoves)
    {
        std::cout << "Game ended in a draw! Due to one of these circumstances - " << std::endl;
        std::cout << "No move rule: neither side could make a move." << std::endl;
        std::cout << "40 turn rule: neither side gained an advantage for 40 consecutive turns, thus the game is a draw" << std::endl;
    }
    else
    {
        std::cout << typeid(*second).name() << " won with " << second->GetPieceCount() << " pieces on the board." << std::endl;
    }

    std::cout << "Goodbye!";

    return 0;
}
