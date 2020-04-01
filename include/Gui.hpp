#include <string>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

#ifndef _GUI_HPP
#define _GUI_HPP

#define WINDOW_NAME "Othello player"

#define DIVIDER_THICKNESS 10
#define DIVIDER_POSITION 0.6

#define BOARD_OFFSET 30
#define BOARD_THICKNESS 4

namespace Gui
{
    // class Disc {
    //     char color;
    //     sf::Vector2f position, size;
    //     bool visible;

    // public:
    //     Disc() {color=BLACK};
    //     Disc(char color, const sf::Vector2f &position, const sf::Vector2f &size,
    //          bool visible=true) 
    //          : color(color), position(position), size(size), visible(visible);
    //     ~Disc() {}
    //     void place(const sf::Vector2f &position, const sf::Vector2f &size)
    //     void draw(sf::RenderWindow &window);
    // };

    class Board {
        int edgeSize, nCells;
        char *cells;

        sf::RectangleShape background;
        sf::RectangleShape *grid;

    public:
        Board() = delete;
        Board(int edgeSize);
        ~Board() {delete cells;}
        void place(const sf::Vector2f &position, const sf::Vector2f &size);
        void draw(sf::RenderWindow &window);
    };

    class Game {
        sf::RenderWindow window;
        sf::RectangleShape divider;
        Board board;

    public:
        Game() = delete;
        Game(unsigned width, unsigned height, int boardSize,
             const std::string windowName=WINDOW_NAME);
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

}
#endif
