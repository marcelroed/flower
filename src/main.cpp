#include <iostream>
#include <SFML/Graphics.hpp>
#include "FieldState.hpp"
#include "Renderer.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>

int main() {
    std::cout << "Hello, World!\n"; 
	sf::RenderWindow window({1024, 800}, "Test");
	window.setFramerateLimit(60);
    sf::CircleShape shape(50);
    shape.setRadius(200);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(sf::Vector2f(50,50));
    FieldState fs;
    Renderer renderer(window, 0.3f, fs);
    sf::Clock deltaClock;
    sf::Time dt;
    std::vector<FluidParticle> particles;
    for (int i = 0; i < 20; i++){
        FluidParticle p(sf::Vector2f(100.0 + i*20.0, 200.0), sf::Vector2f(.0, .0));
        particles.push_back(p);
    }
    // Run while window is open
    while (window.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "Close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        dt = deltaClock.restart();

        // Physics


        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Graphics
        // Window.draw(...);
        //window.draw(shape);
        renderer.render(deltaClock.getElapsedTime());
        // End the current frame
        window.display();
    }
}