#ifndef PIECE_H  // Helps defend program from redefinition compilation errors.
#define PIECE_H

#include <vector>

class Piece
{
private:
    int team = 0;
    int type = 0;
    std::vector<int> currPosition = {0,0};
    std::vector<std::vector<int>> cardinalDir = {{0,0}};

public:
    Piece(int param_type, int param_team, const std::vector<int>& param_currPos, const std::vector<std::vector<int>>& cardinalDir);

    //Getters and Setters
    int getType();

    const std::vector<int>& getCurrPosition();

    const std::vector<std::vector<int>>& getCardinalDir();

    int getTeam();

    void setType(int param_type);

    void setCurrPosition(const std::vector<int>& param_currPosition);
};

#endif