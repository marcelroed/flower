#pragma once
#include <SFML/GpuPreference.hpp>
#include <SFML/Graphics.hpp>
#include "ParticleFieldState.hpp"

class ParticleRenderer{
    public:
        ParticleRenderer(sf::RenderWindow& win, float stepsize, ParticleFieldState& fieldState);
        void render(sf::Time delta_t);
    private:
        sf::RenderWindow& window;
        float stepsize;
        int epochs = 1;
        ParticleFieldState& fieldState;
        ParticleFieldState prevState;
};