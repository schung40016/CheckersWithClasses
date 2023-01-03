#include "piece.h"
#include "board.h"
#include "player.h"
#include "ai.h"
#include "user.h"
#include <queue>
#include "checkersGame.h"

/*
Goals: 
- Create game class and move all main loop code items into game class.
- Refactor some of the calculation code into piece class. 
*/  


int main()
{
    int enemyTurn = 0;
    int turn = 0;
    bool endGame = false;

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

    CheckersGame game(response, enemyTurn);

    // Game Loop.
    while (game.CheckLosers())
    {
        std::cout << "hey" << std::endl;
        endGame = game.Playturn(turn);

        ++turn;

        if (endGame)
        {
            break;
        }
    }

    if (game.CheckTie() || game.GetNoMoves())
    {
        game.PrintDraw();
    }
    else
    {
        game.PrintWinner();
    }

    std::cout << "Goodbye!";

    return 0;
}
