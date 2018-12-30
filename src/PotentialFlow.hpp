#pragma once
#include "ParticleSimulator.hpp"
#include <vector>
#include <functional>
#include <SFML/System/Vector2.hpp>

using Potential = std::function<float(sf::Vector2f)>;

struct particlePointSource{
    sf::Vector2f origin;
    float period;
    int particlesPerTrigger;
    float untilNext = 0.0f;
};

struct particleLineSource{
    sf::Vector2f from;
    sf::Vector2f to;
    float period;
    int particlesPerTrigger;
    float untilNext = 0.0f;
};

struct particlePointDrain{
    sf::Vector2f origin;
    float radius;
};

class PotentialFlow: public ParticleSimulator{
    public:
        void simulate(sf::Time dt);
        void addPotential(Potential p);
        PotentialFlow(ParticleFieldState& fs);
        void addParticlePointSource(float period, int count, sf::Vector2f point);
        void addParticlePointDrain(float radius, sf::Vector2f point);
        void addParticleLineSource(float period, int count, sf::Vector2f from, sf::Vector2f to);
        void clearAll();
        void setLifeTime(float time);

    private:
        std::vector<Potential> potentials;
        std::vector<int> toDelete;
        std::vector<particlePointSource> pointSources;
        std::vector<particleLineSource> lineSources;
        std::vector<particlePointDrain> pointDrains;
        void moveParticle(FluidParticle& particle, sf::Time);
        bool isByDrain(FluidParticle& p);
        float lifeTime = 20.0f;
};

Potential uniform(const float intensity, const sf::Vector2f& direction);
Potential source(const float intensity, const sf::Vector2f& position);
Potential whirl(const float intensity, const sf::Vector2f& position);
Potential doublet(const float intensity, const sf::Vector2f& position);
