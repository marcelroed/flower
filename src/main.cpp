#include <iostream>
#include <SFML/Graphics.hpp>
#include "ParticleFieldState.hpp"
#include "ParticleRenderer.hpp"
#include "ParticleSimulator.hpp"
#include "PotentialFlow.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include "ShapeRenderer.hpp"
#include "helpers.hpp"
#include <algorithm>
#include <fstream>


void outputParticlePos(ParticleFieldState& fs);

enum Mode{
    RANKINES_OVAL, OUTWARD_WHIRL, CIRCLE, /*MAGNUS,*/ SPECIAL
};

int mode = RANKINES_OVAL;
const int width = 1000;
const int height = 1000;




void initializeSimulationMode(int newMode, PotentialFlow& simulator, ShapeRenderer& shapeRenderer){
    mode = newMode;
    switch(mode){
        case RANKINES_OVAL:{
            float distance = 300.0f;
            simulator.addPotential(uniform(90.0f, sf::Vector2f(1.0f, 0.0f)));
            simulator.addPotential(source(6000.0f, sf::Vector2f(width/2 - distance/2, height/2)));
            simulator.addPotential(source(-6000.0f, sf::Vector2f(width/2 + distance/2, height/2)));
            simulator.addParticlePointSource(.3f, 11, sf::Vector2f(width/2 - distance/2, height/2));
            simulator.addParticlePointDrain(20.0f, sf::Vector2f(width/2 + distance/2, height/2));
            simulator.addParticleLineSource(.3f, 41, sf::Vector2f(-5,0), sf::Vector2f(-5, height));
            break;
        }
        case OUTWARD_WHIRL:
            simulator.addPotential(source(12000.0f, sf::Vector2f(width/2, height/2)));
            simulator.addParticlePointSource(.1f, 7, sf::Vector2f(width/2, height/2));
            simulator.addPotential(whirl(24000.0f, sf::Vector2f(width/2, height/2)));
            break;
        /*case MAGNUS: {

            break;
        }*/
        case CIRCLE: {
            float radius = 150.0f;
            sf::CircleShape* circleP = new sf::CircleShape(radius);
            circleP->setFillColor(sf::Color(255,0,0));
            circleP->setPosition(sf::Vector2f(width/2 - radius, height/2 - radius));
            shapeRenderer.addShape(circleP);
            simulator.addPotential(uniform(90.0, sf::Vector2f(1.0f, 0.0f)));
            simulator.addPotential(doublet(2400000.0, sf::Vector2f(width / 2, height / 2)));
            //simulator.addParticlePointSource(0.3f, 10, sf::Vector2f(width/2, height/2));
            simulator.addParticleLineSource(0.3f, 41, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, height));
            //simulator.addPotential(whirl(12000.0, sf::Vector2f(width/2, height/2)));
            //simulator.addPotential(source(12000.0f, sf::Vector2f(0.0,0.0)));
            break;
        }
        case SPECIAL:
            simulator.specialParticles = std::vector<int>({1008, 1029, 1050, 1113, 1156, 1176, 1238, 1240, 1283, 1303, 1346, 1349, 1361, 1363, 1365, 1366, 1388, 1410, 1413, 1422, 1423, 1424, 1426, 1427, 1430, 1473, 1476, 1478, 1483, 1486, 1488, 1489, 1493, 1537, 1540, 1549, 1551, 1555, 1556, 1578, 1600, 1603, 1611, 1620, 1666, 1667, 1673, 1729, 1730, 1735, 1736, 1745, 1746, 1764, 1768, 1785, 1793, 1794, 1795, 1796, 1797, 1806, 1810, 1868, 1869, 1912, 1930, 1931, 1936, 1937, 1976, 1992, 1993, 1998, 2017, 2039, 2041, 2042, 2053, 2055, 2059, 2085, 2104, 2105, 2106, 2116, 2118, 2122, 2126, 2127, 2142, 2146, 2163, 2164, 2165, 2166, 2171, 2172, 2174, 2178, 2179, 2181, 2188, 2205, 2207, 2226, 2227, 2228, 2229, 2231, 2237, 2244, 2247, 2254, 2268, 2270, 2273, 2289, 2294, 2300, 2303, 2304, 2306, 2310, 2312, 2316, 2331, 2336, 2337, 2352, 2357, 2358, 2363, 2367, 2369, 2373, 2374, 2375, 2378, 2394, 2395, 2400, 2402, 2415, 2420, 2421, 2422, 2423, 2426, 2428, 2430, 2432, 2437, 2438, 2443, 2458, 2460, 2464, 2481, 2483, 2487, 2489, 2491, 2493, 2495, 2498, 2500, 2501, 2521, 2523, 2527, 2529, 2542, 2544, 2552, 2553, 2556, 2558, 2564, 2565, 2571, 2584, 2586, 2591, 2605, 2606, 2607, 2615, 2616, 2619, 2621, 2622, 2623, 2627, 2628, 2633, 2649, 2655, 2656, 2669, 2670, 2673, 2674, 2678, 2682, 2684, 2685, 2691, 2698, 2713, 2719, 2736, 2737, 2738, 2739, 2741, 2776, 2782, 2783, 2825, 2839, 2843, 2846, 2907, 2949, 2952, 2971, 3012, 3013, 3035, 3075, 3078, 3099, 3100, 3140, 3163, 3164, 3205, 3226, 3227, 3265, 3267, 3269, 3288, 3289, 3351, 3392, 3394, 3396, 3414, 3457, 3459, 3477, 3519, 3521, 3522, 3540, 3541, 3542, 3543, 3544, 3585});
            std::sort(simulator.specialParticles.rbegin(), simulator.specialParticles.rend());

            simulator.addPotential(source(-35000, sf::Vector2f(width/2, height)));
            simulator.addParticlePointDrain(20.0, sf::Vector2f(width/2, height));
            simulator.addParticleLineSource(0.4, 21, sf::Vector2f(0,0), sf::Vector2f(0, height));
            simulator.addParticleLineSource(0.4, 21, sf::Vector2f(0,0), sf::Vector2f(width, 0));
            simulator.addParticleLineSource(0.4, 21, sf::Vector2f(width,0), sf::Vector2f(width, height));
            break;
        default:
            break;
    }
}

void toggleSimulationMode(PotentialFlow& simulator, ShapeRenderer& shapeRenderer){
    simulator.clearAll();
    shapeRenderer.clearAll();
    if (mode != Mode::SPECIAL){
        mode++;
    }else{
        mode = Mode::RANKINES_OVAL;
    }
    initializeSimulationMode(mode, simulator, shapeRenderer);
}

void potentialFlow(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // Init window
    sf::RenderWindow window({1000, 1000}, "Flower", sf::Style::Default, settings);
    window.setFramerateLimit(120);
    sf::CircleShape shape(50);
    shape.setRadius(200);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(sf::Vector2f(50,50));
    // Initialize state
    ParticleFieldState fs;
    sf::Clock deltaClock;
    sf::Time dt;
    ParticleRenderer particleRenderer(window, 0.3f, fs);
    ShapeRenderer shapeRenderer(window);
    PotentialFlow simulator(fs);
    initializeSimulationMode(RANKINES_OVAL, simulator, shapeRenderer);
    // Testing the fluid state
    /*for (int i = 0; i < 20; i++){
        for (int j = 0; j < 100; j++){
            FluidParticle p(sf::Vector2f(-50.0*j, height/20*i), sf::Vector2f(.0, .0));
            fs.particles.push_back(p);
        }
    }*/
    printf("Particle count: %i\n", fs.particles.size());
    // Run while window is open
    while (window.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:
                    // "Close requested" event: we close the window
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code){
                        case sf::Keyboard::T:
                            toggleSimulationMode(simulator, shapeRenderer);
                            break;
                        case sf::Keyboard::P:
                            outputParticlePos(fs);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        dt = deltaClock.restart();

        // Physics
        simulator.simulate(dt);

        // Graphics
        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Window.draw(...);
        //window.draw(shape);
        shapeRenderer.render(dt);
        particleRenderer.render(deltaClock.getElapsedTime());
        // End the current frame
        window.display();
    }
}

void outputParticlePos(ParticleFieldState& fs){
    std::ofstream output;
    output.open("particlepositions.out");
    for(FluidParticle& particle : fs.particles){
        output << particle.pos.x << " " << particle.pos.y << " " << particle.id << std::endl;
    }
    output.close();
}


void navierStokes(){

}


int main() {
    potentialFlow();
    navierStokes();
    return 0;
}