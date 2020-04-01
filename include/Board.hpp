#include <iostream>
#include <map>
#include <string>
#include <vector>

#ifndef _BOARD_HPP
#define _BOARD_HPP

#define MINIMUM_OTHELLO_BOARD_SIZE 3
#define PASSING_MOVE -1

typedef std::map<int, std::vector<int>> MovesMap;

enum Cell: char {EMPTY = '.', BLACK = 'x', WHITE = 'o'};

class SquareBoard
{
protected:
    int edgeSize, nCells;
    char player;
    std::vector<char> cells;

    bool put(int pos, char cell);

public:
    // Setup
    SquareBoard(int edgeSize);
    ~SquareBoard() {};
    bool print() const;

    // Move handling
    bool validPosition(int pos) {return 0 <= pos && pos < nCells;}
};

class OthelloBoard : public SquareBoard
{
    int blackCount, whiteCount;
public:
    void move(MovesMap &moves, int to);
    // Setup
    OthelloBoard(int edgeSize, char player=BLACK);
    void setPlayer(char player) {this->player = player;}
    void changePlayer() {setPlayer(player == BLACK ? WHITE : BLACK);}
    char getPlayer() {return player;}

    // Move handling
    bool isGameOver();
    int score() const {return blackCount - whiteCount;}
    void exploreDirection(int cellPos, int inc, MovesMap &moves);
    MovesMap getMoves();

    // Algorithms
    int random(const MovesMap& moves);
    int minimax(MovesMap& moves);
};

void printVector(const std::vector<int> &v);
void printMovesMap(const MovesMap &moves);
#endif
