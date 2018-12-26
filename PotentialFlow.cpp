#include "Simulator.cpp"
#include <vector>
#include <functional>
#include <SFML/System/Vector2.hpp>

using Potential = std::function<float(sf::Vector2f)>;

class PotentialFlow: public Simulator{
    public:
        void simulate(float timestep);
        void addPotential(Potential);
        PotentialFlow(FieldState& fs);
    private:
        std::vector<Potential> potentials;
        void moveParticle(FluidParticle& particle, float delta);
};

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

