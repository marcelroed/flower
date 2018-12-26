#include "Renderer.hpp"
#include "FieldState.hpp"
#include <iostream>


Renderer::Renderer(sf::RenderWindow& win, float stepsize, FieldState* stateobj): window(win), stepsize(stepsize), state(stateobj){

}

void Renderer::render(sf::Time delta){
    std::cout << state->particles.size() << std::endl;
    for (FluidParticle particle : state->particles){
        sf::CircleShape circle(10);
        circle.setFillColor(sf::Color(40, 40, 40));
        circle.setPosition(particle.pos);
        window.draw(circle);
    }

    prevState = state;
}