#include "helpers.hpp"
#include <math.h>

float radius(sf::Vector2f vec, sf::Vector2f from){
    sf::Vector2f dist = vec - from;
    return sqrt(pow(dist.x, 2.0f) + pow(dist.y, 2.0f));
}

float length(sf::Vector2f vec){
    return sqrt(pow(vec.x, 2.0f) + pow(vec.y, 2.0f));
}

float angle(sf::Vector2f vec, sf::Vector2f from){
    sf::Vector2f dist = vec - from;
    return atan2(dist.y, dist.x);
}

sf::Vector2f polar(float radius, float angle){
    return sf::Vector2f(radius*cos(angle), radius*sin(angle));
}

float modulus(sf::Vector2f vec){
    return atan2(vec.y, vec.x);
}