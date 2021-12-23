#pragma once
#include "ParticleFieldState.hpp"
#include <SFML/System/Time.hpp>
#include <functional>
class ParticleSimulator{
    public:
        virtual void simulate(sf::Time) = 0;
        explicit ParticleSimulator(ParticleFieldState& fs);
        ParticleFieldState& fieldState;
    protected:
        static sf::Vector2f gradient(const std::function<float(sf::Vector2f)>& p, sf::Vector2f pos, float stepSize);
};