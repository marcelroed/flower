#include <iostream>
#include <SFML/Graphics.hpp>
#include "FieldState.hpp"
#include "Renderer.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>

int main() {
    std::cout << "Hello, World!\n";
    // Init window
	sf::RenderWindow window({1024, 800}, "Test");
	window.setFramerateLimit(60);

    sf::CircleShape shape(50);
    shape.setRadius(200);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(sf::Vector2f(50,50));
    // Initialize state
    FieldState fs;
    sf::Clock deltaClock;
    sf::Time dt;
    Renderer renderer(window, 0.3f, &fs);
    // Testing the fluid state
    for (int i = 0; i < 20; i++){
        FluidParticle p(sf::Vector2f(100.0 + i*40.0, 200.0), sf::Vector2f(.0, .0));
        fs.particles.push_back(p);
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


        // Graphics
        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Window.draw(...);
        //window.draw(shape);
        renderer.render(deltaClock.getElapsedTime());
        // End the current frame
        window.display();
    }
}