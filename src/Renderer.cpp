#include "Renderer.hpp"
#include "FieldState.hpp"



Renderer::Renderer(sf::RenderWindow& win, float stepsize, FieldState stateobj): window(win), stepsize(stepsize), state(stateobj){
    for (FluidParticle particle : state.particles){
        sf::CircleShape circle(2);
        circle.setFillColor(sf::Color(40, 40, 40));
        circle.setPosition(particle.pos);
        win.draw(circle);
    }

    prevState = state;
}

void Renderer::render(sf::Time delta){
    
}