#include "board.hpp"

using namespace std;

void printVector(const std::vector<int> &v) {
    if (v.empty()) {
        cout << "<empty vector>" << endl;
        return;
    }
    for (const auto &it: v) {
        std::cout << it << " " << std::endl;
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
    int start = this->edgeSize / 2 - 1 + (this->edgeSize / 2 - 1) * this->edgeSize;
    this->put(start, WHITE);
    this->put(start + 1, BLACK);
    this->put(start + this->edgeSize, BLACK);
    this->put(start + this->edgeSize + 1, WHITE);
}

vector<int> OthelloBoard::getVerticalMoves(int pos) {
    vector<int> ans;
    if (!this->valid_position(pos)) {
        return ans;
    }

    int i = pos;
    char player = cells[pos];
    char opponent = cells[pos] == BLACK ? WHITE : BLACK;
    // Look up
    for (i = pos - this->edgeSize; i >= 0 && this->cells[i] == opponent; i -= this->edgeSize);
    if (pos - i > this->edgeSize) ans.push_back(i);
    // Look down
    for (i = pos + this->edgeSize; i < this->cellCount && this->cells[i] == opponent; i += this->edgeSize);
    if (i - pos > this->edgeSize) ans.push_back(i);
    return ans;
}

vector<int> OthelloBoard::getHorizontalMoves(int pos) {
    vector<int> ans;
    if (!this->valid_position(pos)) {
        return ans;
    }

    int i = pos;
    char player = cells[pos];
    char opponent = cells[pos] == BLACK ? WHITE : BLACK;
    // Look left
    for (i = pos - 1; i >= pos - pos % this->edgeSize && this->cells[i] == opponent; i -= 1);
    if (pos - i > 1) ans.push_back(i);
    // Look down
    for (i = pos + 1; i < pos - pos % this->edgeSize + this->edgeSize && this->cells[i] == opponent; i += 1);
    if (i - pos > 1) ans.push_back(i);
    return ans;
}

vector<int> OthelloBoard::getMoves(char player /*BLACK or WHITE*/) {
    vector<int> moves = {};
    for (size_t i = 0; i < this->cells.size(); ++i){
        if (this->cells[i] != player) {
            continue;
        }
        // Analyze vertical lines
        vector<int> ans = this->getVerticalMoves(i);
        cout << "Analyzing " << i << ", vertical moves vector: ";
        printVector(ans);
        // Analyze horizontal lines
        ans = this->getHorizontalMoves(i);
        cout << "Analyzing " << i << ", horizontal moves vector: ";
        printVector(ans);
        // Analyze NW-SE diagonals
        // Analyze NE-SW diagonals
    }
    return moves;
}