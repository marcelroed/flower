#pragma once
#include "FieldState.hpp"
#include <SFML/System/Time.hpp>
class Simulator{
    public:
        virtual void simulate(sf::Time) = 0;
        Simulator(FieldState& fs);
        FieldState& fieldState;
};