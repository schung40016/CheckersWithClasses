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
    printBlock(userTurn, rowCount, 0, 3, playerDir);

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
    printBlock(enemyTurn, rowCount, 5, 8, enemyDir);
}

void Board::drawBoard ()
{
    std::cout << "\n\n\n";
    for (int i = board.size() - 1; i >= 0; --i)
    {
        std::cout << i << " " << char(-70); 
        for (size_t j{0}; j < board[i].size(); ++j)
        {
            board[i][j].getType() == 32 ? std::cout << "  " : std::cout << char(board[i][j].getType()) << " ";
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

void Board::printBlock(int team, int rowSize, int start, int end, const std::vector<std::vector<int>>& pieceDir)
{
    for (int i = start; i < end; ++i)
    {
        std::vector<Piece> tempRow;
        if (i % 2 == 0) // Check if even row.
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

bool Board::outOfBounds(std::vector<int> param_position)
{
    if (param_position[0] < 0 || param_position[0] > board.size() || param_position[1] < 0 || param_position[1] > board[0].size())
    {
        return true;
    }
    return false;
}

// TO-DO: Work on this method.
bool Board::isJumpPiece(Piece mainPiece, int turn)
{
    std::vector<std::vector<int>> cardinalDir = mainPiece.getCardinalDir();
    std::vector<int> currPosition = mainPiece.getCurrPosition();

    //std::cout << "G/O: {" << currPosition[0] << ", " << currPosition[1] << "}" << (char)board[currPosition[0]][currPosition[1]].getType() << std::endl;

    for (std::vector<int> pos : cardinalDir)
    {
        int newX = currPosition[0] + pos[1];
        int newY = currPosition[1] + pos[0];

        if (outOfBounds({newX, newY}))
        {
            continue;
        }

        if (!(board[newX][newY].getTeam() == mainPiece.getTeam() || board[newX][newY].getType() == 32))
        {
            newX = currPosition[0] + (pos[1] * 2);
            newY = currPosition[1] + (pos[0] * 2);

            // Check if landing position is blocked.
            if (!outOfBounds({newX, newY})) 
            {
                if (board[newX][newY].getType() == 32)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<std::vector<int>> Board::getJumpPieces(int currentPlayer, int turn)
{
    std::vector<std::vector<int>> jumpPieces = {};

    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            // Check piece's team.
            int pieceTeam = board[i][j].getTeam();

            if (pieceTeam == currentPlayer)
            {
                if (isJumpPiece(board[i][j], turn))
                {   
                    // We found a jump piece, get the position of that piece. 
                    jumpPieces.push_back({i, j});
                }
            } 
        }
    }
    return jumpPieces;
}

std::vector<std::vector<int>> Board::getLegalPieces(int currentPlayer, int turn)
{
    std::vector<std::vector<int>> pieceList;

    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            // Ignore empty pieces.
            if (board[i][j].getType() != 0)
            {
                int pieceTeam = board[i][j].getTeam();

                if (getAllMoves(board[i][j], turn).size() > 0 && pieceTeam == currentPlayer)
                {
                    pieceList.push_back({i, j});
                    continue;
                }   
            }
        }
    }

    return pieceList;
}

std::vector<std::vector<int>> Board::getAllMoves(Piece mainPiece, int turn)
{
    std::vector<std::vector<int>> potentialMoves = mainPiece.getCardinalDir();
    std::vector<std::vector<int>> result;
    std::vector<std::vector<int>> jumpMoves;
    std::vector<int> currPosition = mainPiece.getCurrPosition();

    // Determine available directional moves.
    potentialMoves = mainPiece.getCardinalDir();

    for (std::vector<int> pos : potentialMoves)
    {
        int newX = currPosition[0] + pos[1];
        int newY = currPosition[1] + pos[0];

        // Check if invalid space.
        if (outOfBounds({newX, newY}))
        {
            continue;
        }
        // Check potential jumps.
        else if (!(board[newX][newY].getTeam() == mainPiece.getTeam() || board[newX][newY].getType() == 32))
        {
            newX = currPosition[0] + (pos[1] * 2);
            newY = currPosition[1] + (pos[0] * 2);

            if (!outOfBounds({newX, newY}))
            {
                drawBoard();

                // Check if landing position is blocked.
                if (board[newX][newY].getType() == 32)
                {
                    jumpMoves.push_back({newX, newY});
                }
            }
        }
        else if (board[newX][newY].getType() == 32)
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
    board[newX][newY] = board[currMoveX][currMoveX];
    board[newX][newY].setCurrPosition(board[currMoveX][currMoveX].getCurrPosition());
    board[currMoveX][currMoveY] = temp;
    board[currMoveX][currMoveY].setCurrPosition(temp.getCurrPosition());
}

void Board::HighlightMove(int x, int y)
{
    board[x][y].setType('X');
}

void Board::EraseHighlight(int x, int y)
{
    board[x][y].setType(' ');
}

void Board::CheckKingPiece(int x, int y, bool isPlayer)
{
    // Any super pieces to transform?
    if (x == board.size() && isPlayer)
    {
        board[x][y].getType() == regFirstPiece ? board[x][y].setType(kingFirstPiece) : board[x][y].setType(kingSecPiece);
    }
    else if(x == 0 && !isPlayer)
    {
        board[x][y].getType() == regFirstPiece ? board[x][y].setType(kingFirstPiece) : board[x][y].setType(kingSecPiece);
    }
}

std::vector<std::vector<Piece>>& Board::getBoard()
{
    return this->board;
}