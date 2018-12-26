#pragma once
#include <SFML/GpuPreference.hpp>
#include <SFML/Graphics.hpp>
#include "FieldState.hpp"

class Renderer{
    public:
        Renderer(sf::RenderWindow& win, float stepsize, FieldState stateobj);
        void render(sf::Time delta_t);
    private:
        sf::RenderWindow& window;
        float stepsize;
        int epochs = 1;
        FieldState state;
        FieldState prevState;
};