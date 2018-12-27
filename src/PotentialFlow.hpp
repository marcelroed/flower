#pragma once
#include "Simulator.hpp"
#include <vector>
#include <functional>
#include <SFML/System/Vector2.hpp>

using Potential = std::function<float(sf::Vector2f)>;

class PotentialFlow: public Simulator{
    public:
        void simulate(sf::Time dt);
        void addPotential(Potential p);
        Potential uniform(float strength, sf::Vector2f direction);
        Potential source(float strength, sf::Vector2f position);
        Potential whirlpool(float strength, sf::Vector2f position);
        Potential doublet(float strength, sf::Vector2f position);
        PotentialFlow(FieldState& fs);
    private:
        std::vector<Potential> potentials;
        void moveParticle(FluidParticle& particle, sf::Time);
};