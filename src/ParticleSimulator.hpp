#pragma once
#include "ParticleFieldState.hpp"
#include <SFML/System/Time.hpp>
#include <functional>
class ParticleSimulator{
    public:
        virtual void simulate(sf::Time) = 0;
        ParticleSimulator(ParticleFieldState& fs);
        ParticleFieldState& fieldState;
    protected:
        sf::Vector2f gradient(std::function<float(sf::Vector2f)> p, sf::Vector2f pos, float stepSize);
};