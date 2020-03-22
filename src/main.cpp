#include "board.hpp"

#define BOARD_SIZE 5

int main(int argc, char const *argv[])
{
    OthelloBoard board(BOARD_SIZE);
    board.print();
    board.getMoves(BLACK);

    return 0;
}