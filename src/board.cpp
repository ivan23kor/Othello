#include "board.hpp"

using namespace std;

void printVector(const std::vector<int> &v) {
    if (v.empty()) {
        cout << "<empty vector>" << endl;
        return;
    }
    for (const auto &it: v) {
        cout << it << " ";
    }
    cout << endl;
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

bool SquareBoard::valid_position(int pos) {
    return (0 <= pos && pos < this->cellCount);
}

bool SquareBoard::put(int pos, char cell) {
    if (!this->valid_position(pos)) {
        return false;
    }
    this->cells[pos] = cell;
    return true;
}

OthelloBoard::OthelloBoard(int edgeSize)
        : SquareBoard::SquareBoard(edgeSize) {
    if (edgeSize < MINIMUM_OTHELLO_BOARD_SIZE) {
        cerr << "Minimum Othello board size is " << MINIMUM_OTHELLO_BOARD_SIZE
             << endl;
        exit(1);
    }
    int start = (this->edgeSize + 1) * (this->edgeSize / 2 - 1);
    this->put(12, BLACK);
    this->put(6, WHITE);
    this->put(7, WHITE);
    this->put(8, WHITE);
    this->put(11, WHITE);
    this->put(13, WHITE);
    this->put(16, WHITE);
    this->put(17, WHITE);
    this->put(18, WHITE);
    // this->put(start, WHITE);
    // this->put(start + 1, BLACK);
    // this->put(start + this->edgeSize, BLACK);
    // this->put(start + this->edgeSize + 1, WHITE);
}

bool OthelloBoard::exploreDirection(int cellPos, int inc, char opponent,
                                    vector<int> &moves) {
    int pos = cellPos + inc;
    for (; pos >= 0 /* upper border */
            && pos < this->cellCount /* bottom border */
            && pos % this->edgeSize != 0 /* left border */
            && (pos + 1) % this->edgeSize != 0 /* right border */
            && this->cells[pos] == opponent; /* still on line */
         pos += inc);
    // advanced more than once and found an empty cell
    if (pos - cellPos != inc && this->cells[pos] == EMPTY) {
        moves.push_back(pos);
    }
}

vector<int> OthelloBoard::getMoves(char player /*BLACK or WHITE*/) {
    int pos = 0; // Will be used for move search
    char opponent = player == BLACK ? WHITE : BLACK;
    vector<int> moves = {};
    for (size_t cellPos = 0; cellPos < this->cells.size(); ++cellPos){
        if (this->cells[cellPos] != player) {
            continue;
        }
        // Look left
        this->exploreDirection(cellPos, -1, opponent, moves);
        // Look NW
        this->exploreDirection(cellPos, -this->edgeSize - 1, opponent, moves);
        // Look up
        this->exploreDirection(cellPos, -this->edgeSize, opponent, moves);
        // Look NE
        this->exploreDirection(cellPos, -this->edgeSize + 1, opponent, moves);
        // Look right
        this->exploreDirection(cellPos, 1, opponent, moves);
        // Look SE
        this->exploreDirection(cellPos, +this->edgeSize + 1, opponent, moves);
        // Look down
        this->exploreDirection(cellPos, this->edgeSize, opponent, moves);
        // Look SW
        this->exploreDirection(cellPos, this->edgeSize - 1, opponent, moves);
        printVector(moves);
    }
    return moves;
}