#include "PotentialFlow.hpp"
#include <iostream>

void PotentialFlow::simulate(sf::Time dt){
    // Apply a state change to every particle.
    for(FluidParticle& particle : fieldState.particles){
        moveParticle(particle, dt);
    }
}
// Needs to use the derivative and timescale. Might also need a variable step size.
void PotentialFlow::moveParticle(FluidParticle& particle, sf::Time dt){
    particle.pos += sf::Vector2f(100.0f, 0.0f)*dt.asSeconds();
}

float numericalDerivative(Potential p, sf::Vector2f pos, sf::Vector2f dir, sf::Time dt){

}

PotentialFlow::PotentialFlow(FieldState& fs): Simulator(fs){
}

void PotentialFlow::addPotential(Potential p){
    potentials.push_back(p);
}

