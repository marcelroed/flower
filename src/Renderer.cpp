#include "Renderer.hpp"
#include "ParticleFieldState.hpp"
#include <iostream>


Renderer::Renderer(sf::RenderWindow& win, float stepSize, FieldState& stateObj): window(win), stepsize(stepSize), fieldState(stateObj){

}

void Renderer::render(sf::Time dt){
    for (FluidParticle& particle : fieldState.particles){
        sf::CircleShape circle(7);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(particle.pos);
        window.draw(circle);
    }

    //prevState = state;
}