#include <SFML/System/Vector2.hpp>

class FluidParticle{
    public:
        sf::Vector2f pos;
        sf::Vector2f vel;
        float weight = 0;
        FluidParticle(sf::Vector2f pos, sf::Vector2f vel);
};

