#include <string>
#include <SFML/Graphics.hpp>

const std::string WINDOW_NAME = "Othello player";

#define DIVIDER_THICKNESS 20
#define DIVIDER_POSITION 0.7

class Gui {
    sf::RenderWindow window;
    sf::VideoMode mode;
    sf::RectangleShape divider;

public:
    Gui() = delete;
    Gui(float height, float width, const std::string &windowName=WINDOW_NAME);
    ~Gui() {};
    void run();
};
