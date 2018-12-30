#include <iostream>
#include <SFML/Graphics.hpp>
#include "ParticleFieldState.hpp"
#include "ParticleRenderer.hpp"
#include "ParticleSimulator.hpp"
#include "PotentialFlow.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <math.h>


enum Mode{
    RANKINES_OVAL, OUTWARD_WHIRL
};

int mode = RANKINES_OVAL;
const int width = 1000;
const int height = 1000;




void initializeSimulationMode(int newMode, PotentialFlow& simulator){
    mode = newMode;
    switch(mode){
        case RANKINES_OVAL:
            simulator.addPotential(uniform(90.0f, sf::Vector2f(1.0f, 0.0f)));
            simulator.addPotential(source(6000.0f, sf::Vector2f(width/2, height/2)));
            simulator.addPotential(source(-6000.0f, sf::Vector2f(width/2 + 300.0f, height/2)));
            simulator.addParticlePointSource(.3f, 11, sf::Vector2f(width/2, height/2));
            simulator.addParticlePointDrain(20.0f, sf::Vector2f(width/2 + 300.0f, height/2));
            simulator.addParticleLineSource(.3f, 41, sf::Vector2f(-5,0), sf::Vector2f(-5, height));
            break;
        case OUTWARD_WHIRL:
            simulator.addPotential(source(12000.0, sf::Vector2f(width/2, height/2)));
            simulator.addParticlePointSource(.1f, 5, sf::Vector2f(width/2, height/2));
            simulator.addPotential(whirl(24000.0, sf::Vector2f(width/2, height/2)));
            break;
        default:
            break;
    }
}

void toggleSimulationMode(PotentialFlow& simulator){
    simulator.clearAll();
    if (mode != Mode::OUTWARD_WHIRL){
        mode++;
    }else{
        mode = Mode::RANKINES_OVAL;
    }
    initializeSimulationMode(mode, simulator);
}

void potentialFlow(){
    // Init window
    sf::RenderWindow window({1000, 1000}, "Flower");
    window.setFramerateLimit(120);
    sf::CircleShape shape(50);
    shape.setRadius(200);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(sf::Vector2f(50,50));
    // Initialize state
    ParticleFieldState fs;
    sf::Clock deltaClock;
    sf::Time dt;
    ParticleRenderer renderer(window, 0.3f, fs);
    PotentialFlow simulator(fs);
    initializeSimulationMode(RANKINES_OVAL, simulator);
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
            switch(event.type){
                case sf::Event::Closed:
                    // "Close requested" event: we close the window
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::T){
                        toggleSimulationMode(simulator);
                    }
                    break;
                default:
                    break;
            }
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