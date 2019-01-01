#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class ShapeRenderer;

using job = std::function<void(ShapeRenderer, sf::Time)>;

class ShapeRenderer {
    public:
        void render(sf::Time dt);
        ShapeRenderer(sf::RenderWindow& win);
        void addShape(sf::Shape* shape);
        void clearAll();
        void addJob(job);
        std::vector<sf::Shape*> shapes;
    private:
        sf::RenderWindow& window;
        std::vector<job> jobs;
};
