//
// Created by Marcel on 27/12/2018.
//

#include "helpers.hpp"
#include <math.h>

float radius(sf::Vector2f vec, sf::Vector2f from){
    sf::Vector2f dist = vec - from;
    return sqrt(pow(dist.x, 2.0f), pow(dist.y, 2.0f));
}

float radius(sf::Vector2f vec, sf::Vector2f from){
    sf::Vector2f dist = vec - from;
    return atan2(dist.y, dist.x);
}