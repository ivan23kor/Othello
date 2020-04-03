#include <iostream>
#include "Gui.hpp"

using namespace sf;
using namespace std;


Game::Game(OthelloBoard &board, const std::string windowName)
        : board(board.getEdgeSize()) {
    // Center window
    sf::VideoMode mode = VideoMode::getDesktopMode();
    int width = mode.width * WINDOW_SCALE, height = mode.height * WINDOW_SCALE;
    window.create(VideoMode(width, height), windowName);
    window.setPosition(Vector2i(mode.width * (1 - WINDOW_SCALE) / 2,
                                mode.height * (1 - WINDOW_SCALE) / 2));

    // Board and score dividing line
    divider = RectangleShape(Vector2f(DIVIDER_THICKNESS, height));
    divider.setFillColor(Color::Black);
    divider.setPosition(height, 0);

    // Place board in the center of the left part
    this->board.place(Vector2f(BOARD_OFFSET, BOARD_OFFSET),
        Vector2f(height - 2 * BOARD_OFFSET, height - 2 * BOARD_OFFSET));

    this->board.update(board.copyCells());
}

void Game::play() {
    Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                cout << "Closing the window." << endl;
                window.close();
                return;
            }
        }

        window.clear(Color::White);
        board.draw(window);
        window.draw(divider);
        window.display();
    }
}

Board::Board(int edgeSize) {
    this->edgeSize = edgeSize;
    nCells = edgeSize * edgeSize;

    base.background.setFillColor(Color(0, 160, 12));
    base.background.setOutlineColor(Color::Black);
    base.background.setOutlineThickness(BOARD_THICKNESS);

    base.grid = vector<RectangleShape> (2 * (edgeSize - 1),
                                        RectangleShape(Vector2f(0, 0)));
    for (auto &line: base.grid) {
        line.setFillColor(Color::Black);
    }

    discs = vector<CircleShape> (nCells, CircleShape(0));
    // Set discs to be invisible in the beginning ...
    for (int i = 0, size = discs.size(); i < size; ++i) {
        discs[i].setFillColor(Color::Transparent);
    }
    // ... except for the initial
    int start = (edgeSize + 1) * (edgeSize / 2 - 1);
    discs[start].setFillColor(Color::White);
    discs[start + 1].setFillColor(Color::Black);
    discs[start + edgeSize].setFillColor(Color::White);
    discs[start + edgeSize + 1].setFillColor(Color::Black);
}

void Board::update(vector<char> cells) {
    for (int i = 0, e = cells.size(); i < e; ++i) {
        if (cells[i] == BLACK) {
            discs[i].setFillColor(Color::Black);
        } else if (cells[i] == WHITE) {
            discs[i].setFillColor(Color::White);
        } else {
            discs[i].setFillColor(Color::Transparent);
        }
    }
}

void Board::place(const sf::Vector2f &position, const sf::Vector2f &size) {
    // For grid lines
    float left = position.x, top = position.y;
    base.step = size.x / (float)edgeSize; // presume the board is always square

    base.background.setPosition(position);
    base.background.setSize(size);

    for (int i = 0; i < edgeSize - 1; ++i) {
        // Vertical
        base.grid[i].setSize(Vector2f(BOARD_THICKNESS, size.y));
        base.grid[i].setPosition(left + (i + 1) * base.step, top);
        // Horizontal
        base.grid[i + edgeSize - 1].setSize(Vector2f(size.x, BOARD_THICKNESS));
        base.grid[i + edgeSize - 1].setPosition(left, top + (i + 1) * base.step);
        base.grid[i + edgeSize - 1].setRotation(0);
    }

    float radius = DISC_RADIUS_RATIO * base.step;
    float shift = (base.step - 2 * radius) / 2;
    for (auto &disc: discs) {
        disc.setRadius(radius);
    }
    for (int i = 0, size = discs.size(); i < size; ++i) {
        discs[i].setPosition(position.x + (i % edgeSize) * base.step + shift,
                             position.y + (i / edgeSize) * base.step + shift);
    }
}

void Board::draw(sf::RenderWindow &window) {
    window.draw(base.background);
    for (int i = 0; i < 2 * (edgeSize - 1); ++i) {
        window.draw(base.grid[i]);
    }
    for (auto &disc: discs) {
        window.draw(disc);
    }
}
