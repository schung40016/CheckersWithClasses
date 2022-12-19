#include "board.h"

Board::Board (int userTurn, int enemyTurn)
{
    int rowCount = 8;
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

    for (int i = ((boardLength - 1) * boardLength); i >= 0; i -= 8)
    {
        std::cout << (i / 8) << " " << char(-70); 

        for (int j = i; j < (i + 8); ++j)
        {
            board[j].GetType() == 32 ? std::cout << "  " : std::cout << char(board[j].GetType()) << " ";
        }

        std::cout << std::endl;
    }
    
    std::cout  << "  " << char(-56); 
    for (size_t i{0}; i < 16; ++i)
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
        if (i % 8 == 0)
        {
            if ((i / 8) % 2 == 0)
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

bool Board::OutOfBounds(std::vector<int> param_position)
{
    // If X and Y are within the bounds
    if (!(param_position[0] >= 0 && param_position[0] < boardWidth) || !(param_position[1] >= 0 && param_position[1] < boardLength))
    {
        return true;
    }
    return false;
}

bool Board::IsJumpPiece(Piece mainPiece, int turn)
{
    std::vector<std::vector<int>> cardinalDir = mainPiece.GetCardinalDir();
    std::vector<int> currPosition = mainPiece.GetConvCurrPos();
    int currentPos = mainPiece.GetCurrPosition();

    for (std::vector<int> pos : cardinalDir)
    {
        int newX = currPosition[0] + pos[1];
        int newY = currPosition[1] + pos[0];

        if (OutOfBounds({newX, newY}))
        {
            continue;
        }

        int newPos = (currentPos + (pos[1] * 8)) + (pos[0]);

        if (!(board[newPos].GetTeam() == mainPiece.GetTeam() || board[newPos].GetType() == noTeam))
        {
            newX = currPosition[0] + (pos[1] * 2);
            newY = currPosition[1] + (pos[0] * 2);

            // Check if landing position is blocked.
            if (!OutOfBounds({newX, newY})) 
            {
                int newPos = (currentPos + ((pos[1] * 2) * 8)) + (pos[0] * 2);

                if (board[newPos].GetType() == 32)
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
    std::vector<std::vector<int>> potentialMoves = mainPiece.GetCardinalDir();
    std::vector<int> result;
    std::vector<int> jumpMoves;
    std::vector<int> currPosition = mainPiece.GetConvCurrPos();
    int currentPos = mainPiece.GetCurrPosition();

    // Determine available directional moves.
    potentialMoves = mainPiece.GetCardinalDir();

    for (std::vector<int> pos : potentialMoves)
    {
        int newX = currPosition[0] + pos[1];
        int newY = currPosition[1] + pos[0];

        int newPos = (currentPos + (pos[1] * 8)) + (pos[0]);

        // Check if invalid space.
        if (OutOfBounds({newX, newY}))
        {
            continue;
        }
        // Check potential jumps.
        else if (!(board[newPos].GetTeam() == mainPiece.GetTeam() || board[newPos].GetType() == 32))
        {
            newX = currPosition[0] + (pos[1] * 2);
            newY = currPosition[1] + (pos[0] * 2);

            if (!OutOfBounds({newX, newY}))
            {
                newPos = (currentPos + ((pos[1] * 2) * 8)) + (pos[0] * 2);

                // Check if landing position is blocked.
                if (board[newPos].GetType() == 32)
                {
                    jumpMoves.push_back(newPos);
                }
            }
        }
        else if (board[newPos].GetType() == noTeam)
        {
            result.push_back(newPos);
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
    board[pos].SetType(' ');
    board[pos].SetTeam(noTeam);
    board[pos].SetCardinalDir({{}});
}

void Board::CheckKingPiece(int currPos, bool isPlayer)
{
    // Any super pieces to transform?
    if (((currPos / boardLength == 7) && isPlayer) || (((currPos / boardLength == 0)) && !isPlayer))
    {
        board[currPos].GetType() == regFirstPiece ? board[currPos].Promote(kingFirstPiece) : board[currPos].Promote(kingSecPiece);
        
        // Player gained advantage, reset turn tracker.
        turnTracker = 0;
    }
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