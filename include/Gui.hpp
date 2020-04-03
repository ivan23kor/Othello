#include <string>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

#ifndef _GUI_HPP
#define _GUI_HPP

#define WINDOW_NAME "Othello player"
#define WINDOW_SCALE 0.9

#define DIVIDER_THICKNESS 10
#define DIVIDER_POSITION 0.6

#define BOARD_OFFSET 30
#define BOARD_THICKNESS 4

#define DISC_RADIUS_RATIO 0.4

typedef struct Base_
{
    sf::RectangleShape background;
    std::vector<sf::RectangleShape> grid;
    float step;
} Base;

class Board {
    int edgeSize, nCells;
    Base base;
    std::vector<sf::CircleShape> discs;

public:
    Board() = delete;
    Board(int edgeSize);
    ~Board() {}
    void update(std::vector<char> cells);
    void place(const sf::Vector2f &position, const sf::Vector2f &size);
    void draw(sf::RenderWindow &window);
};

class Game {
    sf::RenderWindow window;
    sf::RectangleShape divider;
    Board board;

public:
    Game() = delete;
    Game(OthelloBoard &board, const std::string windowName=WINDOW_NAME);
    ~Game() {};
    void play();
};

// class Score
// {
//     sf::Vector2i position;
//     sf::Vector2i size;
//     int score;
// public:
//     Score();
//     ~Score();
// };

#endif
