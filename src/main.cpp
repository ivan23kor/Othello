#include <cstdlib>
#include <iostream>
#include "Agent.hpp"
#include "Board.hpp"
#include "Gui.hpp"

using namespace std;

void printResult(const OthelloBoard &board) {
    int score = board.score();
    cout << "********************************************************************************" << endl;
    cout << "Final board position:" << endl;
    board.print();
    cout << "Game over, ";
    if (score > 0) {
        cout << "black wins with the score of +" << score;
    } else if (score < 0) {
        cout << "white wins with the score of " << score;
    } else {
        cout << "draw";
    }
    cout << '.' << endl;
    cout << "********************************************************************************" << endl;
}

void playNoGUI(OthelloBoard &board, Agent &agent1, Agent &agent2) {
    int move = PASSING_MOVE;
    bool agentToPlay = true; // true for first player's turn, false otherwise

    int count = 1;
    while (!board.isGameOver()) {
        cout << " Move #" << count++ << endl;
        board.print();

        board.exploreMoves();
        move = agentToPlay ? agent1.getMove() : agent2.getMove();
        board.move(move);

        cout << "===================================================\n" << endl;
        agentToPlay ^= 1;
    }

    printResult(board);    
}

void playGUI(OthelloBoard &board) {
    Game game(board);
    game.play();
}


int main(int argc, char const *argv[]) {
    bool GUI = false;

    int board_size = atoi(argv[1]);
    if (board_size < MINIMUM_OTHELLO_BOARD_SIZE) {
        cout << "Got invalid board size " << board_size;
        cout << ". Changing the board size to " << MINIMUM_OTHELLO_BOARD_SIZE;
        cout << endl;
        board_size = MINIMUM_OTHELLO_BOARD_SIZE;
    }
    OthelloBoard board(board_size);
    Agent agent1(true, board);
    Agent agent2(false, board);

    if (GUI) {
        playGUI(board);
    } else {
        playNoGUI(board, agent1, agent2);
    }

    return 0;
}
