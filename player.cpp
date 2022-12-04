#include "player.h"

Player::Player (int turn, int pieceCount, bool isPlayer)
{
    //time(NULL)
    srand (2);
    this->turn = turn;
    this->pieceCount = pieceCount;
    this->isPlayer = isPlayer;
}

void Player::performJumpMove(Board& board, std::vector<std::vector<int>>& jumpPieces, Player enemyPlayer, int turn)
{
    int currX = 0;
    int currY = 0;
    Piece newJumpPos = board.getBoard()[0][0];
    std::vector<std::vector<int>> moves = {};

    if (isPlayer)
    {
        std::string playerResponse = "";

        do 
        {
            // Ask for a jump move.
            while (true)
            {
                board.drawBoard();

                std::cout << "You have a piece to jump.\n";
                std::cin >> playerResponse;

                currX = playerResponse[1] - '0';
                currY = playerResponse[0] - '0';

                if (findMove(jumpPieces, {currX, currY}) == false)
                {
                    continue;
                }
                break;
            }

            moves = board.getAllMoves(board.getBoard()[currX][currY], turn);

            newJumpPos = execPlayerMove(board, moves, {currX, currY}, true);

            jumpPieces = board.getJumpPieces(this->turn, turn);

            enemyPlayer.setTakePiece();
        } while (board.isJumpPiece(newJumpPos, turn));
    }
    else
    {
        int randomInt;
        std::vector<int> newMove = {};

        do 
        {
            board.drawBoard();

            randomInt = rand() % jumpPieces.size();

            // Get a random jump move and fetch the positions.
            std::vector<int> currPiece = jumpPieces[randomInt]; 

            moves = board.getAllMoves(board.getBoard()[currPiece[0]][currPiece[1]], turn);

            randomInt = rand() % moves.size();
            newMove = moves[randomInt];

            performMove(board, {{}}, newMove, currPiece, true);
        
            std::cout << "Enemy moved piece {" << currPiece[0] << ", " << currPiece[1] << "} to {" << newMove[0] << ", " << newMove[1] << "}.\n";

            enemyPlayer.setTakePiece();
        } while(board.isJumpPiece(board.getBoard()[newMove[0]][newMove[1]], turn)); 
    }
}

void Player::performRegMove(Board& board, Player& enemyPlayer, int turn)
{
    int currX = 0;
    int currY = 0;
    std::vector<std::vector<int>> moves = {};

    if (isPlayer)
    {
        std::string playerResponse = "";

        while (true)
        {
            board.drawBoard();

            // Ask for regular move.
            std::cout << "Pick a piece to move.\n";
            std::cin >> playerResponse;

            currX = playerResponse[1] - '0';
            currY = playerResponse[0] - '0';

            moves = board.getLegalPieces(this->turn, turn);

            if (!findMove(moves, {currX, currY}))
            {
                std::cout << "This pick has no moves. Try again. \n\n";
                continue;
            }   
            else
            {
                // Error Here: Fetching wrong moves.
                moves = board.getAllMoves(board.getBoard()[currX][currY], turn);

                break;
            }
        }

        execPlayerMove(board, moves, {currX, currY}, false);
    }
    else
    {
        std::cout << "Enemy moved!";
        int randomInt;
        std::vector<int> newMove = {};

        board.drawBoard();

        // Get all legal pieces.
        moves = board.getLegalPieces(this->turn, turn);

        // Fetch a random piece.
        randomInt = rand() % moves.size();
        std::vector<int> currPiece = moves[randomInt];

        // Get all moves for current piece.
        moves = board.getAllMoves(board.getBoard()[currPiece[0]][currPiece[1]], turn);

        randomInt = rand() % moves.size();
        newMove = moves[randomInt];

        performMove(board, {{}}, newMove, currPiece, false);  
        std::cout << "Enemy moved piece {" << currPiece[0] << ", " << currPiece[1] << "} to {" << newMove[0] << ", " << newMove[1] << "}.\n";
    }
}

void Player::performMove(Board& board, const std::vector<std::vector<int>>& moves, const std::vector<int>& newMove, const std::vector<int>& currMove, bool isJump)
{
    int newX = newMove[0];
    int newY = newMove[1];

    if (isJump)
    {
        board.EraseHighlight(((currMove[0]+newX)/2),((currMove[1]+newY)/2));
    }

    board.SwapPieces(currMove[0], currMove[1], newX, newY);

    // Erase highlights.
    if (isPlayer)
    {
        board.EraseHighlight(currMove[0],currMove[1]);

        for (std::vector<int> x : moves)
        {
            if (board.getBoard()[x[0]][x[1]].getType() == 'X')
            {
                board.EraseHighlight(x[0], x[1]);
            }
        }
    }

    board.CheckKingPiece(newX, newY, this->isPlayer);
}

Piece Player::execPlayerMove(Board& board, const std::vector<std::vector<int>>& moves, const std::vector<int>& currMove, bool isJump)
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
        board.drawBoard();

        std::cout << "Pick a spot to move to for that piece.\n";
        std::cin >> choice;

        newX = choice[1] - '0';
        newY = choice[0] - '0';

        if (findMove(moves, {newX, newY}))
        {
            // ERROR: performMove() not working.
            performMove(board, moves, {newX, newY}, currMove, isJump);

            break;
        }
        else
        {
            std::cout << "Bad input\n";
        }
    } while(true);

    return board.getBoard()[newX][newY];
}


bool Player::findMove(const std::vector<std::vector<int>>& moveBank, const std::vector<int>& move)
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

int Player::getTurn()
{
    return this->turn;
}

int Player::getPieceCount()
{
    return this->pieceCount;
}
bool Player::getIsPlayer()
{
    return this->isPlayer;
}

void Player::setTakePiece()
{
    this->pieceCount--;
}