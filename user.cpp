#include "user.h"

User::User(int turn, int pieceCount, bool isPlayer) : Player (turn, pieceCount, isPlayer)
{
}

void User::PerformJumpMove(Board& board, std::vector<int>& jumpPieces, Player& enemyPlayer, int turn)
{
    Piece newJumpPos = board.GetBoard()[0];
    std::vector<int> moves = {};
    int newPos = 0;
    std::string playerResponse = "";

    do 
    {
        // Ask for a jump move.
        while (true)
        {
            board.DrawBoard();

            std::cout << "You have a piece to jump." << std::endl;
            std::cin >> playerResponse;

            newPos = ((playerResponse[1] - '0') * 8) + (playerResponse[0] - '0');

            if (FindMove(jumpPieces, newPos) == false)
            {
                continue;
            }
            break;
        }

        moves = board.GetAllMoves(board.GetBoard()[newPos], turn);

        newJumpPos = ExecPlayerMove(board, moves, newPos, true);

        jumpPieces = board.GetJumpPieces(this->turn, turn);

        enemyPlayer.SetTakePiece(1);
    } while (board.IsJumpPiece(newJumpPos, turn));
}

void User::PerformRegMove(Board& board, Player& enemyPlayer, int turn)
{
    std::vector<int> moves = {};
    int currPos = 0;
    std::string playerResponse = "";

    while (true)
    {
        board.DrawBoard();

        // Ask for regular move.
        std::cout << "Pick a piece to move." << std::endl;;
        std::cin >> playerResponse;

        currPos = ((playerResponse[1] - '0') * 8) + (playerResponse[0] - '0');

        moves = board.GetLegalPieces(this->turn, turn);

        if (!FindMove(moves, currPos))
        {
            std::cout << "This pick has no moves. Try again. \n" << std::endl;
            continue;
        }   
        else
        {
            moves = board.GetAllMoves(board.GetBoard()[currPos], turn);
            break;
        }
    }
    ExecPlayerMove(board, moves, currPos, false);
}

void User::PerformMove(Board& board, const std::vector<int>& moves, int newMove, int currMove, bool isJump)
{
    if (isJump)
    {
        // Calculate the position of the piece we just jumped.
        int takenPiecePos = ((newMove + currMove) / 2);

        board.TakePiece(takenPiecePos);
    }

    board.SwapPieces(currMove, newMove);

    board.EraseHighlight(currMove);

    for (int x : moves)
    {
        if (board.GetBoard()[x].GetType() == 'X')
        {
            board.EraseHighlight(x);
        }
    }

    // Check if player gained advantage or not, respond accordingly.
    isJump ? board.ResetTurnTracker() : board.AddTurnTracker();

    board.CheckKingPiece(newMove, this->isPlayer);
}

Piece User::ExecPlayerMove(Board& board, const std::vector<int>& moves, const int currMove, bool isJump)
{
    std::string choice = " ";
    int newPos = 0;

    do {
        // Highlight moves.
        for (int i = 0; i < moves.size(); ++i)
        {
            board.HighlightMove(moves[i]);
        }        

        // Draw board again.
        board.DrawBoard();

        std::cout << "Pick a spot to move to for that piece." << std::endl;
        std::cin >> choice;

        newPos = ((choice[1] - '0') * 8) + (choice[0] - '0');

        if (FindMove(moves, newPos))
        {
            PerformMove(board, moves, newPos, currMove, isJump);

            break;
        }
        else
        {
            std::cout << "Bad input" << std::endl;
        }
    } while(true);

    return board.GetBoard()[newPos];
}