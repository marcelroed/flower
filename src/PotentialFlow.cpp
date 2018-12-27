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
    sf::Vector2f vel(0.0f, 0.0f);
    for(const Potential& potential : potentials){
        vel += gradient(potential, particle.pos, 0.01f);
    }
    particle.pos += vel;
}

PotentialFlow::PotentialFlow(FieldState& fs): Simulator(fs){
}

void PotentialFlow::addPotential(Potential p){
    potentials.push_back(p);
}

Potential PotentialFlow::uniform(float strength, sf::Vector2f direction){

}
Potential source(float strength, sf::Vector2f position);
Potential whirlpool(float strength, sf::Vector2f position);
Potential doublet(float strength, sf::Vector2f position);

