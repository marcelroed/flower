#pragma once
#include <SFML/System/Vector2.hpp>

float radius(sf::Vector2f vec, sf::Vector2f from);
float angle(sf::Vector2f vec, sf::Vector2f from);
sf::Vector2f polar(float radius, float angle);
float length(sf::Vector2f vec);
float modulus(sf::Vector2f vec);
