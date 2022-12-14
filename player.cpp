#include "player.h"

Player::Player (int turn, int pieceCount, bool isPlayer)
{
    //time(NULL)
    srand (2);
    this->turn = turn;
    this->pieceCount = pieceCount;
    this->isPlayer = isPlayer;
}

void Player::PerformJumpMove(Board& board, std::vector<int>& jumpPieces, Player& enemyPlayer, int turn)
{
    Piece newJumpPos = board.GetBoard()[0];
    std::vector<int> moves = {};
    int newPos = 0;

    if (isPlayer)
    {
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
    else
    {
        int randomInt;
        int newMove = 0;

        do 
        {
            jumpPieces = board.GetJumpPieces(this->turn, turn);

            board.DrawBoard();

            randomInt = rand() % jumpPieces.size();

            // Get a random jump move and fetch the positions.
            int currPiece = jumpPieces[randomInt]; 

            moves = board.GetAllMoves(board.GetBoard()[currPiece], turn);

            randomInt = rand() % moves.size();
            newMove = moves[randomInt];

            PerformMove(board, {}, newMove, currPiece, true);
        
            std::cout << "Enemy moved piece {" << (currPiece / 8) << ", " << (currPiece % 8) << "} to {" << (newMove / 8) << ", " << (newMove % 8) << "}." << std::endl;

            enemyPlayer.SetTakePiece(1);
        } while(board.IsJumpPiece(board.GetBoard()[newMove], turn)); 
    }
}

void Player::PerformRegMove(Board& board, Player& enemyPlayer, int turn)
{
    std::vector<int> moves = {};
    int currPos = 0;

    if (isPlayer)
    {
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
    else
    {
        std::cout << "Enemy moved!";
        int randomInt;
        int newMove = 0;

        board.DrawBoard();

        // Get all legal pieces.
        moves = board.GetLegalPieces(this->turn, turn);

        // Fetch a random piece.
        randomInt = rand() % moves.size();
        int currPiece = moves[randomInt];

        // Get all moves for current piece.
        moves = board.GetAllMoves(board.GetBoard()[currPiece], turn);

        randomInt = rand() % moves.size();
        newMove = moves[randomInt];

        PerformMove(board, {}, newMove, currPiece, false);  
        std::cout << "Enemy moved piece {" << (currPiece / 8) << ", " << (currPiece % 18) << "} to {" << (newMove / 8) << ", " << (newMove % 8) << "}." << std::endl;
    }
}

void Player::PerformMove(Board& board, const std::vector<int>& moves, int newMove, int currMove, bool isJump)
{
    if (isJump)
    {
        // Calculate the position of the piece we just jumped.
        int takenPiecePos = ((newMove + currMove) / 2);

        board.TakePiece(takenPiecePos);
    }

    board.SwapPieces(currMove, newMove);

    // Erase highlights.
    if (isPlayer)
    {
        board.EraseHighlight(currMove);

        for (int x : moves)
        {
            if (board.GetBoard()[x].GetType() == 'X')
            {
                board.EraseHighlight(x);
            }
        }
    }

    // Check if player gained advantage or not, respond accordingly.
    isJump ? board.ResetTurnTracker() : board.AddTurnTracker();

    board.CheckKingPiece(newMove, this->isPlayer);
}

Piece Player::ExecPlayerMove(Board& board, const std::vector<int>& moves, const int currMove, bool isJump)
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