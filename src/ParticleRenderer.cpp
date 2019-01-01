#include "ParticleRenderer.hpp"
#include "ParticleFieldState.hpp"
#include <iostream>


ParticleRenderer::ParticleRenderer(sf::RenderWindow& win, float stepSize, ParticleFieldState& stateObj): window(win), stepsize(stepSize), fieldState(stateObj){

}

void ParticleRenderer::render(sf::Time dt){
    for (FluidParticle& particle : fieldState.particles){
        sf::CircleShape circle(7);
        circle.setFillColor(particle.color);
        circle.setPosition(particle.pos);
        window.draw(circle);
    }

    //prevState = state;
}