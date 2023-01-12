#include "board.h"

Board::Board (int userTurn, int enemyTurn)
{
    int rowCount = boardWidth;
    std::vector<std::vector<int>> playerDir = {{-1, 1}, {1, 1}};
    std::vector<std::vector<int>> enemyDir = {{-1, -1}, {1, -1}};

    // Set enemy pieces.
    PrintBlock(userTurn, rowCount, 0, 24, playerDir);

    // Set Middle space.
    for (int i = 24; i < 40; ++i)
    {
        board.emplace_back(Piece(' ', noTeam, i, {{0, 0}}));
    }

    // Set player pieces.
    PrintBlock(enemyTurn, rowCount, 40, 64, enemyDir);
}

void Board::DrawBoard ()
{
    std::cout << "\n\n\n";

    for (int i = ((boardLength - 1) * boardLength); i >= 0; i -= boardLength)
    {
        std::cout << (i / boardLength) << " " << char(-70); 

        for (int j = i; j < (i + boardWidth); ++j)
        {
            board[j].GetType() == 32 ? std::cout << "  " : std::cout << char(board[j].GetType()) << " ";
        }

        std::cout << std::endl;
    }
    
    std::cout  << "  " << char(-56); 
    for (size_t i{0}; i < (boardWidth * 2); ++i)
    {
        std::cout << char(-51);
    }
    std::cout << std::endl; 
    std::cout << "   0 1 2 3 4 5 6 7" << std::endl;
} 

void Board::PrintBlock(int team, int rowSize, int start, int end, const std::vector<std::vector<int>>& pieceDir)
{
    bool isEvenRow = true;

    for (int i = start; i < end; ++i)
    {
        if (i % boardLength == 0)
        {
            if ((i / boardWidth) % 2 == 0)
            {
                isEvenRow = true;
            }
            else
            {
                isEvenRow = false;
            }
        }

        if (isEvenRow)
        {
            i % 2 == 0 ? board.emplace_back(Piece(team + 1, team, i, pieceDir)) : board.emplace_back(Piece(' ', noTeam, i, pieceDir));
        }
        else
        {
            i % 2 == 1 ? board.emplace_back(Piece(team + 1, team, i, pieceDir)) : board.emplace_back(Piece(' ', noTeam, i, pieceDir));
        }
    }
}

bool Board::IsJumpPiece(Piece mainPiece, int turn)
{
    std::vector<int> newPositions = mainPiece.GetMovePos(boardWidth, boardLength);
    std::vector<int> jumpPositions = mainPiece.GetJumpPos(boardWidth, boardLength);

    for (int i = 0; i < newPositions.size(); ++i)
    {
        if (newPositions[i] == -1)
        {
            continue;
        }

        if (!(board[newPositions[i]].GetTeam() == mainPiece.GetTeam() || board[newPositions[i]].GetType() == noTeam))
        {
            if (jumpPositions[i] != -1) 
            {
                if (board[jumpPositions[i]].GetType() == noTeam)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<int> Board::GetJumpPieces(int currentPlayer, int turn)
{
    std::vector<int> jumpPieces = {};

    for (int i = 0; i < board.size(); ++i)
    {
        // Check piece's team.
        if (board[i].GetTeam() == currentPlayer)
        {
            if (IsJumpPiece(board[i], turn))
            {   
                // We found a jump piece, get the position of that piece. 
                jumpPieces.push_back(i);
            }
        } 
    }
    return jumpPieces;
}

std::vector<int> Board::GetLegalPieces(int currentPlayer, int turn)
{
    std::vector<int> pieceList;

    for (int i = 0; i < board.size(); ++i)
    {
        // Ignore empty pieces.
        if (board[i].GetType() != noTeam)
        {
            int pieceTeam = board[i].GetTeam();

            if (GetAllMoves(board[i], turn).size() > 0 && pieceTeam == currentPlayer)
            {
                pieceList.push_back(i);
                continue;
            }   
        }
    }

    return pieceList;
}

// Not fetching correct moves.
std::vector<int> Board::GetAllMoves(Piece mainPiece, int turn)
{
    std::vector<int> newPositions = mainPiece.GetMovePos(boardWidth, boardLength);
    std::vector<int> jumpPositions = mainPiece.GetJumpPos(boardWidth, boardLength);
    std::vector<int> result;
    std::vector<int> jumpMoves;

    for (int i = 0; i < newPositions.size(); ++i)
    {
        // Check if invalid space.
        if (newPositions[i] == -1)
        {
            continue;
        }
        // Check potential jumps.
        else if (!(board[newPositions[i]].GetTeam() == mainPiece.GetTeam() || board[newPositions[i]].GetType() == noTeam))
        {
            if (jumpPositions[i] != -1)
            {
                // Check if landing position is blocked.
                if (board[jumpPositions[i]].GetType() == noTeam)
                {
                    jumpMoves.push_back(jumpPositions[i]);
                }
            }
        }
        else if (board[newPositions[i]].GetType() == noTeam)
        {
            result.push_back(newPositions[i]);
        }
    }

    if (jumpMoves.size() != 0)
    {
        return jumpMoves;
    }
    
    if (result.size() != 0)
    {
        return result;
    }

    // No moves.
    return {};
}

void Board::SwapPieces(int currMove, int newMove)
{
    Piece temp = board[newMove]; 
    board[newMove] = board[currMove];
    board[newMove].SetCurrPosition(newMove);
    board[currMove] = temp;
    board[currMove].SetCurrPosition(currMove);
}

void Board::HighlightMove(int pos)
{
    board[pos].SetType('X');
}

void Board::EraseHighlight(int pos)
{
    board[pos].SetType(' ');
}

void Board::TakePiece(int pos)
{
    board[pos].ResetPiece(noTeam);
}

void Board::ResetTurnTracker()
{
    this->turnTracker = 0;
}

void Board::AddTurnTracker()
{
    this->turnTracker++;
}

bool Board::CheckTie()
{
    if (turnTracker == turnsForTie)
    {
        return true;
    }

    return false;
}

std::vector<Piece>& Board::GetBoard()
{
    return this->board;
}

int Board::GetTurnTracker()
{
    return this->turnTracker;
}

int Board::GetBoardLength()
{
    return this->boardLength;
}

int Board::GetBoardWidth()
{
    return this->boardWidth;
}