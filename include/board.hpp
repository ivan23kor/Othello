#include <iostream>
#include <string>
#include <vector>

#ifndef _BOARD_HPP
#define _BOARD_HPP
enum Cell: char {EMPTY = '.', BLACK = 'x', WHITE = 'o'};

class SquareBoard
{
protected:
    int edgeSize, cellCount;
    std::vector<char> cells;
    std::vector<int> possibleMoves;
public:
    SquareBoard(int edgeSize);
    ~SquareBoard() {};
    bool print();
    bool valid_position(int pos);
    bool put(int pos, char cell);
};

class OthelloBoard : public SquareBoard
{
public:
    OthelloBoard(int edgeSize);
    std::vector<int> getVerticalMoves(int pos);
    std::vector<int> getHorizontalMoves(int pos);
    std::vector<int> getMoves(char player);
};

void printVector(const std::vector<int> &v);
#endif
