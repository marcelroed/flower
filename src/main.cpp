#include <iostream>
#include <SFML/Graphics.hpp>
#include "ParticleFieldState.hpp"
#include "Renderer.hpp"
#include "Simulator.hpp"
#include "PotentialFlow.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <math.h>

void potentialFlow(){
    // Init window
    const int width = 1000;
    const int height = 1000;
    sf::RenderWindow window({1000, 1000}, "Flower");
    window.setFramerateLimit(60);

    sf::CircleShape shape(50);
    shape.setRadius(200);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(sf::Vector2f(50,50));
    // Initialize state
    FieldState fs;
    sf::Clock deltaClock;
    sf::Time dt;
    Renderer renderer(window, 0.3f, fs);
    PotentialFlow simulator(fs);
    //simulator.addPotential([](sf::Vector2f pos){return 3*pos.x;});
    simulator.addPotential(uniform(90.0f, sf::Vector2f(1.0f, 0.0f)));
    simulator.addPotential(source(6000.0f, sf::Vector2f(width/2, height/2)));
    //simulator.addPotential(source(-3000.0f, sf::Vector2f(width/2 + 300.0f, height/2)));
    simulator.addParticlePointSource(.3f, 10, sf::Vector2f(width/2, height/2));
    simulator.addParticleLineSource(.3f, 40, sf::Vector2f(-5,0), sf::Vector2f(-5, height));
    // Testing the fluid state
    /*for (int i = 0; i < 20; i++){
        for (int j = 0; j < 100; j++){
            FluidParticle p(sf::Vector2f(-50.0*j, height/20*i), sf::Vector2f(.0, .0));
            fs.particles.push_back(p);
        }
    }*/
    printf("Particle count: %i\n", fs.particles.size());
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
        simulator.simulate(dt);

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


void navierStokes(){

}


int main() {
    potentialFlow();
    navierStokes();
    return 0;
}