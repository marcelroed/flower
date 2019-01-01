#include <iostream>
#include <SFML/Graphics.hpp>
#include "ParticleFieldState.hpp"
#include "ParticleRenderer.hpp"
#include "ParticleSimulator.hpp"
#include "PotentialFlow.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include "ShapeRenderer.hpp"
#include "helpers.hpp"


enum Mode{
    RANKINES_OVAL, OUTWARD_WHIRL, CIRCLE, MAGNUS, SPECIAL
};

int mode = RANKINES_OVAL;
const int width = 1000;
const int height = 1000;




void initializeSimulationMode(int newMode, PotentialFlow& simulator, ShapeRenderer& shapeRenderer){
    mode = newMode;
    switch(mode){
        case RANKINES_OVAL:{
            float distance = 300.0f;
            simulator.addPotential(uniform(90.0f, sf::Vector2f(1.0f, 0.0f)));
            simulator.addPotential(source(6000.0f, sf::Vector2f(width/2 - distance/2, height/2)));
            simulator.addPotential(source(-6000.0f, sf::Vector2f(width/2 + distance/2, height/2)));
            simulator.addParticlePointSource(.3f, 11, sf::Vector2f(width/2 - distance/2, height/2));
            simulator.addParticlePointDrain(20.0f, sf::Vector2f(width/2 + distance/2, height/2));
            simulator.addParticleLineSource(.3f, 41, sf::Vector2f(-5,0), sf::Vector2f(-5, height));
            break;
        }
        case OUTWARD_WHIRL:
            simulator.addPotential(source(12000.0f, sf::Vector2f(width/2, height/2)));
            simulator.addParticlePointSource(.1f, 10, sf::Vector2f(width/2, height/2));
            simulator.addPotential(whirl(24000.0f, sf::Vector2f(width/2, height/2)));
            break;
        case MAGNUS: {

            break;
        }
        case CIRCLE: {
            float radius = 150.0f;
            sf::CircleShape* circleP = new sf::CircleShape(radius);
            circleP->setFillColor(sf::Color(255,0,0));
            circleP->setPosition(sf::Vector2f(width/2 - radius, height/2 - radius));
            shapeRenderer.addShape(circleP);
            simulator.addPotential(uniform(90.0, sf::Vector2f(1.0f, 0.0f)));
            simulator.addPotential(doublet(2400000.0, sf::Vector2f(width / 2, height / 2)));
            //simulator.addParticlePointSource(0.3f, 10, sf::Vector2f(width/2, height/2));
            simulator.addParticleLineSource(0.3f, 41, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, height));
            //simulator.addPotential(whirl(12000.0, sf::Vector2f(width/2, height/2)));
            //simulator.addPotential(source(12000.0f, sf::Vector2f(0.0,0.0)));
            break;
        }
        case SPECIAL:
            break;
        default:
            break;
    }
}

void toggleSimulationMode(PotentialFlow& simulator, ShapeRenderer& shapeRenderer){
    simulator.clearAll();
    shapeRenderer.clearAll();
    if (mode != Mode::SPECIAL){
        mode++;
    }else{
        mode = Mode::RANKINES_OVAL;
    }
    initializeSimulationMode(mode, simulator, shapeRenderer);
}

void potentialFlow(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // Init window
    sf::RenderWindow window({1000, 1000}, "Flower", sf::Style::Default, settings);
    window.setFramerateLimit(120);
    sf::CircleShape shape(50);
    shape.setRadius(200);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(sf::Vector2f(50,50));
    // Initialize state
    ParticleFieldState fs;
    sf::Clock deltaClock;
    sf::Time dt;
    ParticleRenderer particleRenderer(window, 0.3f, fs);
    ShapeRenderer shapeRenderer(window);
    PotentialFlow simulator(fs);
    initializeSimulationMode(RANKINES_OVAL, simulator, shapeRenderer);
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
                        toggleSimulationMode(simulator, shapeRenderer);
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
        shapeRenderer.render(dt);
        particleRenderer.render(deltaClock.getElapsedTime());
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