#include "Simulator.hpp"

Simulator::Simulator(ParticleFieldState& fs): fieldState(fs){
    
}

sf::Vector2f Simulator::gradient(std::function<float(sf::Vector2f)> p, sf::Vector2f pos, float h){
    float x = (p(pos + sf::Vector2f(h, 0.0f)) - p(pos - sf::Vector2f(h, 0.0f)))/(2*h);
    float y = (p(pos + sf::Vector2f(0.0f, h)) - p(pos - sf::Vector2f(0.0f, h)))/(2*h);
    return sf::Vector2f(x, y);
}