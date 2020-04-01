#include "Board.hpp"
#include "Gui.hpp"

using namespace std;

#define BOARD_SIZE 3

void printResult(const OthelloBoard &board) {
    int score = board.score();
    cout << "================================================================================" << endl;
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
    cout << "================================================================================" << endl;
}

inline int getTurn(const MovesMap &moves) {
    int turn = 0;
    auto ME = moves.end();

    do {
        cout << "Which one are you choosing? ";
        cin >> turn;
    } while (moves.find(turn) == ME && turn != -1);
    return turn;
}

void playNoGUI(int boardSize) {
    OthelloBoard board(BOARD_SIZE);

    int turn = -1;
    const char human = BLACK;
    MovesMap moves;
    moves = board.getMoves();
    board.minimax(moves);
    return;

    while (!board.isGameOver()) {
        cout << "The board is like that:" << endl;
        board.print();
        moves = board.getMoves();

        if (board.getPlayer() == human) {
            cout << "You can make the following moves:" << endl;
            printMovesMap(moves);

            turn = getTurn(moves);
        } else {
            turn = board.random(moves);
            cout << "I move to " << turn << endl;
        }

        if (turn == PASSING_MOVE) {
            board.changePlayer();
        } else {
            board.move(moves, turn);
        }
        cout << "===================================================\n" << endl;
    }

    printResult(board);    
}

int main(int argc, char const *argv[]) {
    playNoGUI(BOARD_SIZE);

    // sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    // Gui::Game game(mode.width * 0.8, mode.height * 0.8, BOARD_SIZE);
    // game.play();

    return 0;
}
