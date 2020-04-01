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
    for (const auto &[key, value]: moves) {
        cout << "[" << key << "]: ";
        printVector(value);
    }
}

SquareBoard::SquareBoard(int edgeSize) {
    this->edgeSize = edgeSize;
    this->cellCount = edgeSize * edgeSize;
    this->cells = vector<char>(this->cellCount, EMPTY);
}

bool SquareBoard::print() {
    for (size_t i = 0; i < this->cells.size(); ++i)
    {
        cout << this->cells[i] << " ";
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
    int b = blackCount, w = whiteCount;
    return (b > 0 && w == 0) || (w > 0 && b == 0) || (b + w == cellCount);
}

void OthelloBoard::exploreDirection(int cellPos, int inc, MovesMap &moves) {
    vector<int> flips; // positions of the discs to flip
    char opponent = player == BLACK ? WHITE : BLACK;
    int pos = cellPos + inc;
    for (; pos >= 0 && /* upper border */
           pos < this->cellCount && /* bottom border */
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
