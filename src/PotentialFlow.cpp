#include "PotentialFlow.h"

void PotentialFlow::simulate(float timestep){
    // Apply a state change to every particle.
    for(FluidParticle particle : fieldstate.particles){
        
    }
}
// Needs to use the derivative and timescale. Might also need a variable step size.
void PotentialFlow::moveParticle(FluidParticle& particle, float delta){
    //particle.pos += sf::Vector2f(2.0f, 3.0f);
}

float numericalDerivative(Potential p, sf::Vector2f pos, sf::Vector2f dir, float delta){

}

PotentialFlow::PotentialFlow(FieldState& fs): Simulator(fs){
}

void PotentialFlow::addPotential(Potential p){
    potentials.push_back(p);
}

