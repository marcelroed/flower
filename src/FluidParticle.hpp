#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class FluidParticle{
    public:
        sf::Vector2f pos;
        sf::Vector2f vel;
        float weight = 0;
        float age = 0.0f;
        sf::Color color = sf::Color::Green;
        int id = -1;
        FluidParticle(sf::Vector2f pos, sf::Vector2f vel);
};