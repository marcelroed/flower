#include "helpers.hpp"
#include <cmath>

float radius(sf::Vector2f vec, sf::Vector2f from){
    sf::Vector2f dist = vec - from;
    return sqrtf(powf(dist.x, 2.0f) + powf(dist.y, 2.0f));
}

float length(sf::Vector2f vec){
    return sqrtf(powf(vec.x, 2.0f) + powf(vec.y, 2.0f));
}

float angle(sf::Vector2f vec, sf::Vector2f from){
    sf::Vector2f dist = vec - from;
    return std::atan2(dist.y, dist.x);
}

sf::Vector2f polar(float radius, float angle){
    return {static_cast<float>(radius*std::cos(angle)), static_cast<float>(radius*std::sin(angle))};
}

float modulus(sf::Vector2f vec){
    return atan2f(vec.y, vec.x);
}