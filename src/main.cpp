#include <cstdlib>
#include <iostream>
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

inline int readHumanMove(const MovesMap &moves) {
    int move = PASSING_MOVE;
    auto ME = moves.end();

    do {
        cout << "Which one are you choosing? ";
        cin >> move;
    } while (moves.find(move) == ME && move != PASSING_MOVE);
    return move;
}

class Agent
{
    OthelloBoard &board;
    bool AI; // true for AI, false for human
public:
    Agent() = delete;
    Agent(bool AI, OthelloBoard &board) : AI(AI), board(board) {}; // true for AI, false for human
    ~Agent() {}
    int getMove(const MovesMap &moves) {
        int move;
        if (AI) {
            cout << "I can make the following moves:" << endl;
            printMovesMap(moves);
            move = board.greedy(moves);
            cout << "I move to " << move << endl;
        } else {
            cout << "You can make the following moves:" << endl;
            printMovesMap(moves);
            move = readHumanMove(moves);
        }
        return move;
    }
};

void playNoGUI(OthelloBoard &board, Agent &agent1, Agent &agent2) {
    int move = PASSING_MOVE;
    MovesMap moves;
    bool agentToPlay = true; // true for first player's turn, false otherwise

    int count = 1;
    while (!board.isGameOver()) {
        cout << " Move #" << count++ << endl;
        board.print();

        moves = board.getMoves();
        move = agentToPlay ? agent1.getMove(moves) : agent2.getMove(moves);
        board.move(moves, move);

        cout << "===================================================\n" << endl;
        agentToPlay = ~agentToPlay;
    }

    printResult(board);    
}

void playGUI(OthelloBoard &board) {
    Game game(board);
    game.play();
}


int main(int argc, char const *argv[]) {
    bool GUI = true;

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
