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
    this->nCells = edgeSize * edgeSize;
    this->cells = vector<char>(this->nCells, EMPTY);
}

bool SquareBoard::print() const {
    for (size_t i = 0; i < this->cells.size(); ++i)
    {
        // Prepend TAB
        if (i % this->edgeSize == 0) {
            cout << '\t';
        }
        // Print cell
        cout << this->cells[i] << " ";
        // Append newline
        if ((i + 1) % this->edgeSize == 0) {
            cout << endl;
        }
    }
    return true;
}

bool SquareBoard::put(int pos, char cell) {
    if (!this->validPosition(pos)) {
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
           pos < this->nCells && /* bottom border */
           pos % this->edgeSize != 0 && /* left border */
           (pos + 1) % this->edgeSize != 0 && /* right border */
           this->cells[pos] == opponent; /* still on line */
           pos += inc) {
        flips.push_back(pos);
    }
     // advanced more than once and found an empty cell
    if (pos - cellPos != inc && this->cells[pos] == EMPTY) {
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
