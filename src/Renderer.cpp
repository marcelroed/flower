#include "Renderer.hpp"
#include "FieldState.hpp"
#include <iostream>


Renderer::Renderer(sf::RenderWindow& win, float stepsize, FieldState& stateobj): window(win), stepsize(stepsize), fieldState(stateobj){

}

void Renderer::render(sf::Time delta){
    for (FluidParticle& particle : fieldState.particles){
        sf::CircleShape circle(10);
        circle.setFillColor(sf::Color(40, 40, 40));
        circle.setPosition(particle.pos);
        window.draw(circle);
    }

    //prevState = state;
}