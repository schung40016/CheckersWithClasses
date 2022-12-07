#include "board.h"

// None: 
// Black:
// White: 

Board::Board (int userTurn, int enemyTurn)
{
    int rowCount = 8;
    std::vector<std::vector<int>> playerDir = {{-1, 1}, {1, 1}};
    std::vector<std::vector<int>> enemyDir = {{-1, -1}, {1, -1}};

    // Set enemy pieces.
    PrintBlock(userTurn, rowCount, 0, 3, playerDir);

    // Set Middle space.
    for (int i = 3; i < 5; ++i)
    {
        std::vector<Piece> tempRow;
        for (int j = 0; j < rowCount; ++j)
        {
            tempRow.emplace_back(Piece(' ', noTeam, {i, j}, {{0, 0}}));
        }
        board.emplace_back(tempRow);
    }

    // Set player pieces.
    PrintBlock(enemyTurn, rowCount, 5, 8, enemyDir);
}

void Board::DrawBoard ()
{
    std::cout << "\n\n\n";
    for (int i = board.size() - 1; i >= 0; --i)
    {
        std::cout << i << " " << char(-70); 
        for (size_t j{0}; j < board[i].size(); ++j)
        {
            board[i][j].GetType() == 32 ? std::cout << "  " : std::cout << char(board[i][j].GetType()) << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "  "<< char(-56); 
    for (size_t i{0}; i < board.size() * 2; ++i)
    {
        std::cout << char(-51);
    }
    std::cout << "\n"; 
    std::cout << "   0 1 2 3 4 5 6 7\n";
} 

void Board::PrintBlock(int team, int rowSize, int start, int end, const std::vector<std::vector<int>>& pieceDir)
{
    for (int i = start; i < end; ++i)
    {
        std::vector<Piece> tempRow;
        if (i % 2 == 0) 
        {
            for (int j = 0; j < rowSize; ++j)
            {
                j % 2 == 0 ? tempRow.emplace_back(Piece(team + 1, team, {i, j}, pieceDir)) : tempRow.emplace_back(Piece(' ', noTeam, {i, j}, pieceDir));
            }
        }
        else
        {
            for (int j = 0; j < rowSize; ++j)
            {
                j % 2 == 1 ? tempRow.emplace_back(Piece(team + 1, team, {i, j}, pieceDir)) : tempRow.emplace_back(Piece(' ', noTeam, {i, j}, pieceDir));
            }
        }
        board.emplace_back(tempRow);
    }
}

bool Board::OutOfBounds(std::vector<int> param_position)
{
    // If X and Y are within the bounds
    if (!(param_position[0] >= 0 && param_position[0] < board.size()) || !(param_position[1] >= 0 && param_position[1] < board[0].size()))
    {
        return true;
    }
    return false;
}

bool Board::IsJumpPiece(Piece mainPiece, int turn)
{
    std::vector<std::vector<int>> cardinalDir = mainPiece.GetCardinalDir();
    std::vector<int> currPosition = mainPiece.GetCurrPosition();

    for (std::vector<int> pos : cardinalDir)
    {
        int newX = currPosition[0] + pos[1];
        int newY = currPosition[1] + pos[0];

        if (OutOfBounds({newX, newY}))
        {
            continue;
        }
        if (!(board[newX][newY].GetTeam() == mainPiece.GetTeam() || board[newX][newY].GetType() == 32))
        {
            newX = currPosition[0] + (pos[1] * 2);
            newY = currPosition[1] + (pos[0] * 2);

            // Check if landing position is blocked.
            if (!OutOfBounds({newX, newY})) 
            {
                if (board[newX][newY].GetType() == 32)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<std::vector<int>> Board::GetJumpPieces(int currentPlayer, int turn)
{
    std::vector<std::vector<int>> jumpPieces = {};

    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            // Check piece's team.
            if (board[i][j].GetTeam() == currentPlayer)
            {
                if (IsJumpPiece(board[i][j], turn))
                {   
                    // We found a jump piece, get the position of that piece. 
                    jumpPieces.push_back({i, j});
                }
            } 
        }
    }
    return jumpPieces;
}

std::vector<std::vector<int>> Board::GetLegalPieces(int currentPlayer, int turn)
{
    std::vector<std::vector<int>> pieceList;

    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            // Ignore empty pieces.
            if (board[i][j].GetType() != noTeam)
            {
                int pieceTeam = board[i][j].GetTeam();

                if (GetAllMoves(board[i][j], turn).size() > 0 && pieceTeam == currentPlayer)
                {
                    pieceList.push_back({i, j});
                    continue;
                }   
            }
        }
    }

    return pieceList;
}

std::vector<std::vector<int>> Board::GetAllMoves(Piece mainPiece, int turn)
{
    std::vector<std::vector<int>> potentialMoves = mainPiece.GetCardinalDir();
    std::vector<std::vector<int>> result;
    std::vector<std::vector<int>> jumpMoves;
    std::vector<int> currPosition = mainPiece.GetCurrPosition();

    // Determine available directional moves.
    potentialMoves = mainPiece.GetCardinalDir();

    for (std::vector<int> pos : potentialMoves)
    {
        int newX = currPosition[0] + pos[1];
        int newY = currPosition[1] + pos[0];

        // Check if invalid space.
        if (OutOfBounds({newX, newY}))
        {
            continue;
        }
        // Check potential jumps.
        else if (!(board[newX][newY].GetTeam() == mainPiece.GetTeam() || board[newX][newY].GetType() == 32))
        {
            newX = currPosition[0] + (pos[1] * 2);
            newY = currPosition[1] + (pos[0] * 2);

            if (!OutOfBounds({newX, newY}))
            {
                DrawBoard();

                // Check if landing position is blocked.
                if (board[newX][newY].GetType() == 32)
                {
                    jumpMoves.push_back({newX, newY});
                }
            }
        }
        else if (board[newX][newY].GetType() == noTeam)
        {
            result.push_back({newX, newY});
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

void Board::SwapPieces(int currMoveX, int currMoveY, int newX, int newY)
{
    Piece temp = board[newX][newY]; 
    board[newX][newY] = board[currMoveX][currMoveY];
    board[newX][newY].SetCurrPosition({newX,newY});
    board[currMoveX][currMoveY] = temp;
    board[currMoveX][currMoveY].SetCurrPosition({currMoveX, currMoveY});
}

void Board::HighlightMove(int x, int y)
{
    board[x][y].SetType('X');
}

void Board::EraseHighlight(int x, int y)
{
    board[x][y].SetType(' ');
}

void Board::TakePiece(int x, int y)
{
    board[x][y].SetType(' ');
    board[x][y].SetTeam(noTeam);
    board[x][y].SetCardinalDir({{}});
}

void Board::CheckKingPiece(int x, int y, bool isPlayer)
{
    // Any super pieces to transform?
    if ((x == (board.size() - 1)  && isPlayer) || (x == 0 && !isPlayer))
    {
        board[x][y].GetType() == regFirstPiece ? board[x][y].Promote(kingFirstPiece) : board[x][y].Promote(kingSecPiece);
    }
}

std::vector<std::vector<Piece>>& Board::GetBoard()
{
    return this->board;
}