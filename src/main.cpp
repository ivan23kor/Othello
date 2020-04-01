#include "Board.hpp"
#include "Gui.hpp"

#define BOARD_SIZE 4

using namespace std;


void printResult(const OthelloBoard &board) {
    int score = board.score();
    cout << "Game over, ";
    if (score > 0) {
        cout << "black wins with the score of +" << score;
    } else if (score < 0) {
        cout << "white wins with the score of " << score;
    } else {
        cout << "draw";
    }
    cout << '.' << endl;
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

// int main(int argc, char const *argv[])
// {
//     OthelloBoard board(BOARD_SIZE);

//     int turn = -1;
//     const char human = BLACK;
//     MovesMap moves;

//     while (!board.isGameOver()) {
//         cout << "The board is like that:" << endl;
//         board.print();
//         moves = board.getMoves();

//         if (board.getPlayer() == human) {
//             cout << "You can make the following moves:" << endl;
//             printMovesMap(moves);

//             turn = getTurn(moves);
//         } else {
//             turn = board.random(moves);
//             cout << "I move to " << turn << endl;
//         }

//         if (turn == PASSING_MOVE) {
//             board.changePlayer();
//         } else {
//             board.move(moves, turn);
//         }
//         cout << "===================================================\n" << endl;
//     }

//     printResult(board);

//     return 0;
// }

int main(int argc, char const *argv[]) {
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    Gui app(mode.height, mode.width);
    app.run();

    return 0;
}
