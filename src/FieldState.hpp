#include <vector>
#include "FluidParticle.hpp"

class FieldState{
    public:
        std::vector<FluidParticle> particles;
        FieldState();
};