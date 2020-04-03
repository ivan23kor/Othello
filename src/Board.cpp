#include <iomanip>
#include <iostream>
#include "Board.hpp"

using namespace std;

const int INF = std::numeric_limits<int>::max();
const int nINF = std::numeric_limits<int>::min(); // negative infinity


void printVector(const vector<int> &v) {
    if (v.empty()) {
        cout << "<empty vector>" << endl;
        return;
    }
    for (const auto &it: v) {
        cout << it << " ";
    }
    cout << endl;
}

void printMovesMap(const MovesMap &moves) {
    if (moves.empty()) {
        cout << "<empty map>" << endl;
        return;
    }
    for (const auto &[moves, flips]: moves) {
        cout << "[" << moves << "]: ";
        printVector(flips);
    }
}

SquareBoard::SquareBoard(int edgeSize) {
    this->edgeSize = edgeSize;
    nCells = edgeSize * edgeSize;
    cells = vector<char>(nCells, EMPTY);
}

bool SquareBoard::print() const {
    // Print color
    // cout << "\033[2;40m" << " " << "\033[0m";
    if (player == BLACK) {
        cout << "\033[;40m\033[1;37m" << "B " << "\033[0m\033[0m";
    } else {
        cout << "\033[;47m\033[1;30m" << "W " << "\033[0m\033[0m";
    }

    for (size_t i = 0; i < cells.size(); ++i)
    {
        // Prepend TAB
        if (i % edgeSize == 0) {
            cout << '\t';
        }

        // Print cell
        cout << cells[i];
        // if (cells[i] == BLACK) {
        //     cout << "\033[;40m" << "bb" << "\033[0m";
        // } else if (cells[i] == WHITE) {
        //     cout << "\033[;47m\033[1;30m" << "ww" << "\033[0m\033[0m";
        // } else {
        //     cout << "\033[;42m" << "  " << "\033[0m";;
        // }

        // Print the index board besides
        if ((i + 1) % edgeSize == 0) {
            cout << "\t\t";
            for (int j = i - edgeSize + 1; j <= i; ++j){
                cout << setfill(' ') << setw(3) << j;
            }
            cout << endl;
        }
    }
    return true;
}

bool SquareBoard::put(int pos, char cell) {
    if (!validPosition(pos)) {
        return false;
    }
    cells[pos] = cell;
    return true;
}

OthelloBoard::OthelloBoard(int edgeSize, char player)
                           : SquareBoard::SquareBoard(edgeSize) {
    if (edgeSize < MINIMUM_OTHELLO_BOARD_SIZE) {
        cerr << "Minimum Othello board size is " << MINIMUM_OTHELLO_BOARD_SIZE
             << endl;
        exit(1);
    }

    setPlayer(player);

    blackCount = 2;
    whiteCount = 2;

    int start = (edgeSize + 1) * (edgeSize / 2 - 1);
    // put(5, WHITE);
    // put(6, WHITE);
    // put(9, BLACK);
    // put(11, BLACK);
    put(start, WHITE);
    put(start + 1, BLACK);
    put(start + edgeSize, BLACK);
    put(start + edgeSize + 1, WHITE);
}

bool OthelloBoard::isGameOver() {
    int curPlayerNMoves = getMoves().size();
    changePlayer(); // change to opponent
    int opponentNMoves = getMoves().size();
    changePlayer(); // change back to the current player
    return curPlayerNMoves == 0 && opponentNMoves == 0;
}

void OthelloBoard::exploreDirection(int cellPos, int inc, MovesMap &moves) {
    vector<int> flips; // positions of the discs to flip
    char opponent = player == BLACK ? WHITE : BLACK;
    int pos = cellPos + inc;
    for (; pos >= 0 && /* upper border */
           pos < nCells && /* bottom border */
           pos % edgeSize != 0 && /* left border */
           (pos + 1) % edgeSize != 0 && /* right border */
           cells[pos] == opponent; /* still on line */
           pos += inc) {
        flips.push_back(pos);
    }
     // advanced more than once and found an empty cell
    if (pos - cellPos != inc && cells[pos] == EMPTY) {
        moves[pos].insert(moves[pos].end(), flips.begin(), flips.end());
    }
}

MovesMap OthelloBoard::getMoves() {
    static size_t cellPos = 0; // index for player cell iteration
    MovesMap moves;
    for (cellPos = 0; cellPos < cells.size(); ++cellPos){
        if (cells[cellPos] != player) {
            continue;
        }
        // Look left
        exploreDirection(cellPos, -1, moves);
        // Look NW
        exploreDirection(cellPos, -edgeSize - 1, moves);
        // Look up
        exploreDirection(cellPos, -edgeSize, moves);
        // Look NE
        exploreDirection(cellPos, -edgeSize + 1, moves);
        // Look right
        exploreDirection(cellPos, 1, moves);
        // Look SE
        exploreDirection(cellPos, edgeSize + 1, moves);
        // Look down
        exploreDirection(cellPos, edgeSize, moves);
        // Look SW
        exploreDirection(cellPos, edgeSize - 1, moves);
    }
    return moves;
}

void OthelloBoard::move(MovesMap &moves, int to) {
    if (to == PASSING_MOVE) {
        changePlayer();
        return;
    }

    cells[to] = player;
    for (const auto &flip: moves[to]) {
        cells[flip] = player;
    }

    int nFlips = moves[to].size();
    if (player == BLACK) {
        blackCount += nFlips + 1;
        whiteCount -= nFlips;
    } else {
        blackCount -= nFlips;
        whiteCount += nFlips + 1;
    }

    changePlayer();
}

int OthelloBoard::random(const MovesMap& moves) {
    return moves.begin()->first;
}

int OthelloBoard::greedy(const MovesMap& moves) {
    int bestMove = PASSING_MOVE, bestLen = 0;
    for (auto &[to, flips]: moves) {
        if (flips.size() > bestLen) {
            bestLen = flips.size();
            bestMove = to;
        }
    }
    return bestMove;
}

int OthelloBoard::minimax(MovesMap& moves) {
    int max = nINF, min = INF;

    int i,j,value = 1;

    if (isGameOver()) {
        return score();
    }

    vector<int> scores(moves.size(), 0);
    for (auto &[move, flips]: moves) {
        cout << "Making move " << move << endl;
        this->move(moves, move);
    }
//         for(i=0;i<9;i++)
//             {
//                  if(board[i] == '*')
//                 {
//                     if(min_val>max_val) // reverse of pruning condition.....
//                   {
//                       if(flag == true)
//                    {
//                      board[i] = 'X';
//                      value = minimax(false);
//                    }
//                     else
//                     {
//                       board[i] = 'O';
//                       value = minimax(true);
//                     }
//                   board[i] = '*';
//                   score[i] = value;
//                  }
//                }
//             }

//         if(flag == true)
//         {
//                  max_val = -1000;
//                  for(j=0;j<9;j++)
//                 {
//                     if(score[j] > max_val && score[j] != 1)
//                     {
//                         max_val = score[j];
//                         index1 = j;
//                     }
//                 }
//                 return max_val;
//         }
//         if(flag == false)
//         {
//                 min_val = 1000;
//                 for(j=0;j<9;j++)
//                 {
//                     if(score[j] < min_val && score[j] != 1)
//                     {
//                         min_val = score[j];
//                         index1 = j;
//                     }
//                 }
//             return min_val;
//         }
// }
    return 0;
}
