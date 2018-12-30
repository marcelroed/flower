#pragma once
#include <vector>
#include "FluidParticle.hpp"

class ParticleFieldState{
    public:
        std::vector<FluidParticle> particles;
        ParticleFieldState();
};