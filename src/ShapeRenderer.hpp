#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ShapeRenderer {
    public:
        void render();
        ShapeRenderer(sf::RenderWindow& win);
        void addShape(sf::Shape* shape);
        void clearAll();
    private:
        sf::RenderWindow& window;
        std::vector<sf::Shape*> shapes;
};
