#include <iostream>
#include "Gui.hpp"

using namespace sf;
using namespace std;


Gui::Game::Game(unsigned width, unsigned height, int boardSize,
                const std::string windowName) : board(boardSize) {
    // Center window
    window.create(VideoMode(width, height), windowName);
    window.setPosition(window.getPosition() / 2);

    board.place(Vector2f(BOARD_OFFSET, BOARD_OFFSET),
                Vector2f(height - 2 * BOARD_OFFSET, height - 2 * BOARD_OFFSET));

    // Board and score dividing line
    this->divider = RectangleShape(Vector2f(DIVIDER_THICKNESS, height));
    divider.setFillColor(Color::Black);
    divider.setPosition(height, 0);
}

void Gui::Game::play() {
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

Gui::Board::Board(int edgeSize) {
    this->edgeSize = edgeSize;
    nCells = edgeSize * edgeSize;

    // Init board
    cells = new char[nCells];
    for (int i = 0; i < nCells; ++i) {
        cells[i] = EMPTY;
    }
    int start = (edgeSize + 1) * (edgeSize / 2 - 1);
    cells[start] = WHITE;
    cells[start + 1] = BLACK;
    cells[start + edgeSize] = BLACK;
    cells[start + edgeSize + 1] = WHITE;

    background.setFillColor(Color(0, 160, 12));
    background.setOutlineColor(Color::Black);
    background.setOutlineThickness(BOARD_THICKNESS);

    this->grid = new RectangleShape[2 * (edgeSize - 1)];
    for (int i = 0; i < 2 * (edgeSize - 1); ++i) {
        grid[i] = RectangleShape(Vector2f(0, 0));
        grid[i].setFillColor(Color::Black);
    }
}

void Gui::Board::place(const sf::Vector2f &position, const sf::Vector2f &size) {
    // For grid lines
    float left = position.x, top = position.y;
    float stepX = size.x / edgeSize, stepY = size.y / edgeSize;

    background.setPosition(position);
    background.setSize(size);

    for (int i = 0; i < edgeSize - 1; ++i) {
        // Vertical
        grid[i].setSize(Vector2f(BOARD_THICKNESS, size.y));
        grid[i].setPosition(left + (i + 1) * stepX, top);
        // Horizontal
        grid[i + edgeSize - 1].setSize(Vector2f(size.x, BOARD_THICKNESS));
        grid[i + edgeSize - 1].setPosition(left, top + (i + 1) * stepY);
        grid[i + edgeSize - 1].setRotation(0);
    }
}

void Gui::Board::draw(sf::RenderWindow &window) {
    window.draw(background);
    for (int i = 0; i < 2 * (edgeSize - 1); ++i) {
        window.draw(grid[i]);
    }
}
