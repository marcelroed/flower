#include "PotentialFlow.hpp"
#include <iostream>
#include <math.h>
#include "helpers.hpp"
#include <algorithm>

void PotentialFlow::simulate(sf::Time dt){
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
                FluidParticle p = newParticle(pos);
                fieldState.particles.push_back(p);
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
                FluidParticle p = newParticle(pos);
                fieldState.particles.push_back(p);
                //printf("Particle count: %i\n", fieldState.particles.size());
            }
        }
    }

    // Apply a state change to every particle
    int index = 0;
    for(FluidParticle& particle : fieldState.particles){
        particle.age += dt.asSeconds();
        if (particle.age > lifeTime || isByDrain(particle)){
            toDelete.push_back(index);
        }
        moveParticle(particle, dt);
        index++;
    }
    // Delete old and off-screen particles
    std::sort(toDelete.rbegin(), toDelete.rend());
    for (int index : toDelete){
        fieldState.particles.erase(fieldState.particles.begin() + index);
    }
    toDelete.clear();
}

FluidParticle PotentialFlow::newParticle(sf::Vector2f position){
    FluidParticle newParticle(position, sf::Vector2f(0,0));
    newParticle.id = particlesSpawned;
    if (specialParticles.size() && specialParticles.back() == particlesSpawned){
        newParticle.color = sf::Color::Red;
        specialParticles.pop_back();
    }
    particlesSpawned++;
    return newParticle;
}

// Needs to use the derivative and timescale. Might also need a variable step size.
void PotentialFlow::moveParticle(FluidParticle& particle, sf::Time dt){
    sf::Vector2f vel(0.0f, 0.0f);
    for(const Potential& potential : potentials){
        vel += gradient(potential, particle.pos, 0.001f);
    }
    particle.pos += vel*dt.asSeconds();

}

PotentialFlow::PotentialFlow(ParticleFieldState& fs): ParticleSimulator(fs){
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

bool PotentialFlow::isByDrain(FluidParticle& p){
    for(particlePointDrain& ppd : pointDrains){
        if (radius(ppd.origin, p.pos) < ppd.radius){
            return true;
        }
    }
}


void PotentialFlow::clearAll() {
    potentials.clear();
    pointDrains.clear();
    pointSources.clear();
    fieldState.particles.clear();
    lineSources.clear();
    particlesSpawned = 0;
    specialParticles.clear();
}

void PotentialFlow::addParticlePointDrain(float radius, sf::Vector2f point) {
    particlePointDrain d{point, radius};
    pointDrains.push_back(d);
}

void  PotentialFlow::setLifeTime(float time) {
    lifeTime = time;
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