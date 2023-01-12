#include "ai.h"

Ai::Ai(int turn, int pieceCount, bool isPlayer) : Player (turn, pieceCount, isPlayer)
{
    srand((unsigned) time(NULL));
}

void Ai::PerformJumpMove(Board& board, std::vector<int>& jumpPieces, Player& enemyPlayer, int turn)
{
    Piece newJumpPos = board.GetBoard()[0];
    std::vector<int> moves = {};
    int newPos = 0;

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

void Ai::PerformRegMove(Board& board, Player& enemyPlayer, int turn)
{
    std::vector<int> moves = {};
    int currPos = 0;
    
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
    std::cout << "Enemy moved piece {" << (currPiece % 8) << ", " << (currPiece / 8) << "} to {" << (newMove % 8) << ", " << (newMove / 8) << "}." << std::endl;
}

void Ai::PerformMove(Board& board, const std::vector<int>& moves, int newMove, int currMove, bool isJump)
{
    if (isJump)
    {
        // Calculate the position of the piece we just jumped.
        int takenPiecePos = ((newMove + currMove) / 2);

        board.TakePiece(takenPiecePos);
    }

    board.SwapPieces(currMove, newMove);

    // Check if player gained advantage or not, respond accordingly.
    isJump ? board.ResetTurnTracker() : board.AddTurnTracker();

    if (board.GetBoard()[newMove].CheckKingPiece(this->isPlayer, board.GetBoardWidth(), board.GetBoardLength()))
    {
        board.ResetTurnTracker();
    }
}