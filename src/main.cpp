#include <iostream>
#include <SFML/Graphics.hpp>
//#include "Renderer.cpp"


int main() {
    std::cout << "Hello, World!\n"; 
	sf::RenderWindow window({1024, 800}, "Test");
	window.setFramerateLimit(60);
    sf::CircleShape shape(50);
    shape.setRadius(200);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(sf::Vector2f(50,50));
    //FieldState fs;
    //Renderer renderer(window, 0.3f, fs);

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

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw everything here...
        // Window.draw(...);
        window.draw(shape);
        // End the current frame
        window.display();
    }
}