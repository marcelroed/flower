#pragma once
#include "Simulator.hpp"
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