#include "PotentialFlow.hpp"
#include <iostream>
#include <math.h>
#include "helpers.hpp"

void PotentialFlow::simulate(sf::Time dt){
    // Delete old and off-screen particles
    for (std::vector<int>::reverse_iterator i = toDelete.rbegin();
         i != toDelete.rend(); ++i ) {
        fieldState.particles.erase(fieldState.particles.begin() + *i);
    }
    toDelete.clear();

    // Spawn new particles from sources
    // Point sources
    for (particlePointSource& pointSource : pointSources){
        pointSource.untilNext -= dt.asSeconds();
        //printf("Until spawntime: %f\n", pointSource.untilNext);
        // Spawn particles if the right amount of time has passed
        if (pointSource.untilNext <= 0){
            // Reset time
            pointSource.untilNext = pointSource.period;
            // Spawn the right number of particles around point
            double angleDiff = 2*M_PI/pointSource.particlesPerTrigger;
            for(int i = 0; i < pointSource.particlesPerTrigger; i++){
                double angle = i*angleDiff;
                sf::Vector2f pos = pointSource.origin + polar(10.0f, angle);
                //printf("%f, %f\n", pos.x, pos.y);
                FluidParticle newParticle(pos, sf::Vector2f(0,0));
                fieldState.particles.push_back(newParticle);
                //printf("Particle count: %i\n", fieldState.particles.size());
            }
        }
    }

    // Line sources
    for (particleLineSource& lineSource : lineSources){
        lineSource.untilNext -= dt.asSeconds();
        //printf("Until spawntime: %f\n", lineSource.untilNext);
        // Spawn particles if the right amount of time has passed
        if (lineSource.untilNext <= 0){
            // Reset time
            lineSource.untilNext = lineSource.period;
            // Spawn the right number of particles around point
            sf::Vector2f dist = lineSource.to - lineSource.from;
            for(int i = 0; i < lineSource.particlesPerTrigger; i++){
                float fraction = (float)i/(float)lineSource.particlesPerTrigger;
                sf::Vector2f pos = lineSource.from + fraction*dist;
                //printf("%f, %f\n", pos.x, pos.y);
                FluidParticle newParticle(pos, sf::Vector2f(0,0));
                fieldState.particles.push_back(newParticle);
                //printf("Particle count: %i\n", fieldState.particles.size());
            }
        }
    }

    // Apply a state change to every particle
    int index = 0;
    for(FluidParticle& particle : fieldState.particles){
        particle.age += dt.asSeconds();
        if (particle.age > lifeTime){
            toDelete.push_back(index);
        }
        moveParticle(particle, dt);
        index++;
    }
}
// Needs to use the derivative and timescale. Might also need a variable step size.
void PotentialFlow::moveParticle(FluidParticle& particle, sf::Time dt){
    sf::Vector2f vel(0.0f, 0.0f);
    for(const Potential& potential : potentials){
        vel += gradient(potential, particle.pos, 0.01f);
    }
    particle.pos += vel*dt.asSeconds();

}

PotentialFlow::PotentialFlow(FieldState& fs): Simulator(fs){
}

void PotentialFlow::addPotential(Potential p){
    potentials.push_back(p);
}


void PotentialFlow::addParticlePointSource(float period, int count, sf::Vector2f point) {
    particlePointSource s{point, period, count};
    pointSources.push_back(s);
}

void PotentialFlow::addParticleLineSource(float period, int count, sf::Vector2f from, sf::Vector2f to) {
    particleLineSource s{from, to, period, count};
    lineSources.push_back(s);
}

Potential source(const float strength, const sf::Vector2f& position){
    return [strength, position](sf::Vector2f curPos){return strength*log(radius(curPos, position));};
}
Potential whirl(const float strength, const sf::Vector2f& position){
    return [strength, position](sf::Vector2f curPos){return strength*angle(curPos, position);};
}
Potential doublet(const float strength, const sf::Vector2f& position){
    return [strength, position](sf::Vector2f curPos){return strength*cos(angle(curPos, position))/radius(curPos, position);};
}

Potential uniform(const float strength, const sf::Vector2f& direction){
    const sf::Vector2f normalized = direction/radius(direction, sf::Vector2f(0.0,0.0));
    return [strength, normalized](sf::Vector2f curPos){return strength*(curPos.x*normalized.x + curPos.y*normalized.y);};
}