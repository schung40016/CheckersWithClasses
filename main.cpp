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

    std::cout << "isPlayer " << first.getIsPlayer() << " " <<  second.getIsPlayer() << std::endl;

    Board board(user.getTurn(), enemy.getTurn());

    // Game Loop.
    while (user.getPieceCount() != 0 && enemy.getPieceCount() != 0)
    {
        board.drawBoard();
        std::vector<std::vector<int>> jumpPieces;

        // Player 1 goes first. 
        if (turn % 2 == 0)
        {
            jumpPieces = board.getJumpPieces(first.getTurn(), turn);

            if (jumpPieces.size() > 0)
            {
                first.performJumpMove(board, jumpPieces, second, turn);
            }
            else
            {
                first.performRegMove(board, second, turn);
            }
        }
        else
        {
            jumpPieces = board.getJumpPieces(second.getTurn(), turn);

            if (jumpPieces.size() > 0)
            {
                second.performJumpMove(board, jumpPieces, first, turn);
            }
            else
            {
                second.performRegMove(board, first, turn);
            }
        }

        turn++;
    }

    return 0;
}
