#include "piece.h"
#include "board.h"
#include "player.h"
#include <vector>

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

    Player user(response, 12, true);
    Player enemy(enemyTurn, 12, false);

    Player& first = response == 0 ? user : enemy;
    Player& second = response == 1 ? user : enemy;

    Board board(user.GetTurn(), enemy.GetTurn());

    // Game Loop.
    while (user.GetPieceCount() != 0 && enemy.GetPieceCount() != 0)
    {
        board.DrawBoard();
        std::vector<std::vector<int>> jumpPieces;

        std::cout << "Current Score: " << std::endl;
        std::cout << "Player: "<< user.GetPieceCount() << ", Enemy: " << enemy.GetPieceCount() << std::endl;

        jumpPieces = board.GetJumpPieces(first.GetTurn(), turn);

        if (jumpPieces.size() > 0)
        {
            first.PerformJumpMove(board, jumpPieces, second, turn);
        }
        else
        {
            first.PerformRegMove(board, second, turn);
        }

        std::swap(first, second);

        turn++;
    }

    if (user.GetPieceCount() == 0)
    {
        std::cout << "You Lost! " << " The enemy won with " << enemy.GetPieceCount() << " pieces on the board." << std::endl;
    }
    else
    {
        std::cout << "You WON, with " << user.GetPieceCount() << " pieces on the board." << std::endl;
    }

    std::cout << "Goodbye!";

    return 0;
}
