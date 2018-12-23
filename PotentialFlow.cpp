#include "Simulator.cpp"
class PotentialFlow: public Simulator{
    public:
        void simulate(float timestep);
};

void PotentialFlow::simulate(float timestep){
    for(FluidParticle particle : fieldstate.particles){

    }
}