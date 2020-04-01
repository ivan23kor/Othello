#include "Gui.hpp"

using namespace sf;


Gui::Gui(float height, float width, const std::string &windowName) {
    this->window.create(VideoMode(height, width), windowName);

    RectangleShape divider(Vector2f(mode.height, DIVIDER_THICKNESS));
    divider.setFillColor(Color::Black);
    divider.setPosition(Vector2f(mode.width * DIVIDER_POSITION, 0));
}

void Gui::run() {
    Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            return;
        }

        window.clear(Color::White);
        window.draw(divider);
        window.display();
    }
}
