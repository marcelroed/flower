#pragma once
#include <SFML/GpuPreference.hpp>
#include <SFML/Graphics.hpp>
#include "ParticleFieldState.hpp"

class Renderer{
    public:
        Renderer(sf::RenderWindow& win, float stepsize, FieldState& fieldState);
        void render(sf::Time delta_t);
    private:
        sf::RenderWindow& window;
        float stepsize;
        int epochs = 1;
        FieldState& fieldState;
        FieldState prevState;
};