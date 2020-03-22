#include "board.hpp"

#define BOARD_SIZE 4

int main(int argc, char const *argv[])
{
    OthelloBoard board(BOARD_SIZE);
    board.print();
    board.getMoves(WHITE);

    return 0;
}