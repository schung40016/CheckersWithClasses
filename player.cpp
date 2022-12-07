#include "player.h"

Player::Player (int turn, int pieceCount, bool isPlayer)
{
    //time(NULL)
    srand (2);
    this->turn = turn;
    this->pieceCount = pieceCount;
    this->isPlayer = isPlayer;
}

void Player::PerformJumpMove(Board& board, std::vector<std::vector<int>>& jumpPieces, Player& enemyPlayer, int turn)
{
    int currX = 0;
    int currY = 0;
    Piece newJumpPos = board.GetBoard()[0][0];
    std::vector<std::vector<int>> moves = {};

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

                currX = playerResponse[1] - '0';
                currY = playerResponse[0] - '0';

                if (FindMove(jumpPieces, {currX, currY}) == false)
                {
                    continue;
                }
                break;
            }

            moves = board.GetAllMoves(board.GetBoard()[currX][currY], turn);

            newJumpPos = ExecPlayerMove(board, moves, {currX, currY}, true);
 
            jumpPieces = board.GetJumpPieces(this->turn, turn);

            enemyPlayer.SetTakePiece();
        } while (board.IsJumpPiece(newJumpPos, turn));
    }
    else
    {
        int randomInt;
        std::vector<int> newMove = {};

        do 
        {
            jumpPieces = board.GetJumpPieces(this->turn, turn);

            board.DrawBoard();

            randomInt = rand() % jumpPieces.size();

            // Get a random jump move and fetch the positions.
            std::vector<int> currPiece = jumpPieces[randomInt]; 

            moves = board.GetAllMoves(board.GetBoard()[currPiece[0]][currPiece[1]], turn);

            randomInt = rand() % moves.size();
            newMove = moves[randomInt];

            PerformMove(board, {{}}, newMove, currPiece, true);
        
            std::cout << "Enemy moved piece {" << currPiece[0] << ", " << currPiece[1] << "} to {" << newMove[0] << ", " << newMove[1] << "}." << std::endl;;

            enemyPlayer.SetTakePiece();
        } while(board.IsJumpPiece(board.GetBoard()[newMove[0]][newMove[1]], turn)); 
    }
}

void Player::PerformRegMove(Board& board, Player& enemyPlayer, int turn)
{
    int currX = 0;
    int currY = 0;
    std::vector<std::vector<int>> moves = {};

    if (isPlayer)
    {
        std::string playerResponse = "";

        while (true)
        {
            board.DrawBoard();

            // Ask for regular move.
            std::cout << "Pick a piece to move." << std::endl;;
            std::cin >> playerResponse;

            currX = playerResponse[1] - '0';
            currY = playerResponse[0] - '0';

            // Crashes
            moves = board.GetLegalPieces(this->turn, turn);

            if (!FindMove(moves, {currX, currY}))
            {
                std::cout << "This pick has no moves. Try again. \n" << std::endl;;
                continue;
            }   
            else
            {
                moves = board.GetAllMoves(board.GetBoard()[currX][currY], turn);

                break;
            }
        }

        ExecPlayerMove(board, moves, {currX, currY}, false);
    }
    else
    {
        std::cout << "Enemy moved!";
        int randomInt;
        std::vector<int> newMove = {};

        board.DrawBoard();

        // Get all legal pieces.
        moves = board.GetLegalPieces(this->turn, turn);

        // Fetch a random piece.
        randomInt = rand() % moves.size();
        std::vector<int> currPiece = moves[randomInt];

        // Get all moves for current piece.
        moves = board.GetAllMoves(board.GetBoard()[currPiece[0]][currPiece[1]], turn);

        randomInt = rand() % moves.size();
        newMove = moves[randomInt];

        PerformMove(board, {{}}, newMove, currPiece, false);  
        std::cout << "Enemy moved piece {" << currPiece[0] << ", " << currPiece[1] << "} to {" << newMove[0] << ", " << newMove[1] << "}." << std::endl;
    }
}

void Player::PerformMove(Board& board, const std::vector<std::vector<int>>& moves, const std::vector<int>& newMove, const std::vector<int>& currMove, bool isJump)
{
    int newX = newMove[0];
    int newY = newMove[1];

    if (isJump)
    { 
        board.TakePiece(((currMove[0]+newX)/2),((currMove[1]+newY)/2));
    }

    board.SwapPieces(currMove[0], currMove[1], newX, newY);

    // Erase highlights.
    if (isPlayer)
    {
        board.EraseHighlight(currMove[0],currMove[1]);

        for (std::vector<int> x : moves)
        {
            if (board.GetBoard()[x[0]][x[1]].GetType() == 'X')
            {
                board.EraseHighlight(x[0], x[1]);
            }
        }
    }

    board.CheckKingPiece(newX, newY, this->isPlayer);
}

Piece Player::ExecPlayerMove(Board& board, const std::vector<std::vector<int>>& moves, const std::vector<int>& currMove, bool isJump)
{
    std::string choice = " ";
    int newX = 0;
    int newY = 0;

    do {
        // Highlight moves.
        for (int i = 0; i < moves.size(); ++i)
        {
            board.HighlightMove(moves[i][0], moves[i][1]);
        }        

        // Draw board again.
        board.DrawBoard();

        std::cout << "Pick a spot to move to for that piece." << std::endl;
        std::cin >> choice;

        newX = choice[1] - '0';
        newY = choice[0] - '0';

        if (FindMove(moves, {newX, newY}))
        {
            PerformMove(board, moves, {newX, newY}, currMove, isJump);

            break;
        }
        else
        {
            std::cout << "Bad input" << std::endl;
        }
    } while(true);

    return board.GetBoard()[newX][newY];
}


bool Player::FindMove(const std::vector<std::vector<int>>& moveBank, const std::vector<int>& move)
{
    for (size_t i{0}; i < moveBank.size(); i++)
    {
        if (moveBank[i][0] == move[0] && moveBank[i][1] == move[1])
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

void Player::SetTakePiece()
{
    this->pieceCount--;
}