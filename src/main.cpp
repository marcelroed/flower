#include <iostream>
#include <SFML/Graphics.hpp>
#include "ParticleFieldState.hpp"
#include "ParticleRenderer.hpp"
#include "ParticleSimulator.hpp"
#include "PotentialFlow.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <cmath>
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
            simulator.addPotential(source(6000.0f, sf::Vector2f(width/2.0f - distance/2, height/2.0f)));
            simulator.addPotential(source(-6000.0f, sf::Vector2f(width/2.0f + distance/2, height/2.0f)));
            simulator.addParticlePointSource(.3f, 11, sf::Vector2f(width/2.0f - distance/2, height/2.0f));
            simulator.addParticlePointDrain(20.0f, sf::Vector2f(width/2.0f + distance/2, height/2.0f));
            simulator.addParticleLineSource(.3f, 41, sf::Vector2f(-5,0), sf::Vector2f(-5, height));
            break;
        }
        case OUTWARD_WHIRL:
            simulator.addPotential(source(12000.0f, sf::Vector2f(width/2.0f, height/2.0f)));
            simulator.addParticlePointSource(.1f, 7, sf::Vector2f(width/2.0f, height/2.0f));
            simulator.addPotential(whirl(24000.0f, sf::Vector2f(width/2.0f, height/2.0f)));
            break;
        /*case MAGNUS: {
            break;
        }*/
        case CIRCLE: {
            float radius = 150.0f;
            auto* circleP = new sf::CircleShape(radius);
            circleP->setFillColor(sf::Color(255,0,0));
            circleP->setPosition(sf::Vector2f(width/2.0f - radius, height/2.0f - radius));
            shapeRenderer.addShape(circleP);
            simulator.addPotential(uniform(90.0, sf::Vector2f(1.0f, 0.0f)));
            simulator.addPotential(doublet(2400000.0, sf::Vector2f(width / 2.0f, height / 2.0f)));
            //simulator.addParticlePointSource(0.3f, 10, sf::Vector2f(width/2, height/2));
            simulator.addParticleLineSource(0.3f, 41, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, height));
            //simulator.addPotential(whirl(12000.0, sf::Vector2f(width/2, height/2)));
            //simulator.addPotential(source(12000.0f, sf::Vector2f(0.0,0.0)));
            break;
        }
        case SPECIAL:
            simulator.specialParticles = std::vector<int>({1037, 1052, 1083, 1114, 1143, 1144, 1176, 1204, 1237, 1264, 1265, 1282, 1299, 1325, 1327, 1328, 1360, 1361, 1364, 1382, 1385, 1387, 1388, 1389, 1422, 1426, 1427, 1440, 1441, 1442, 1443, 1446, 1447, 1450, 1484, 1488, 1489, 1491, 1492, 1497, 1498, 1502, 1503, 1506, 1507, 1508, 1545, 1546, 1549, 1550, 1551, 1562, 1563, 1566, 1567, 1573, 1607, 1611, 1612, 1623, 1627, 1634, 1669, 1672, 1673, 1683, 1734, 1735, 1742, 1743, 1756, 1769, 1772, 1784, 1796, 1797, 1798, 1799, 1800, 1801, 1802, 1815, 1818, 1830, 1845, 1846, 1874, 1875, 1876, 1908, 1934, 1935, 1939, 1970, 1994, 1995, 2001, 2017, 2031, 2034, 2035, 2052, 2055, 2063, 2075, 2092, 2093, 2095, 2096, 2097, 2098, 2099, 2100, 2112, 2115, 2116, 2121, 2135, 2136, 2138, 2150, 2151, 2152, 2153, 2154, 2157, 2161, 2162, 2163, 2166, 2167, 2172, 2173, 2176, 2182, 2184, 2196, 2201, 2211, 2212, 2213, 2214, 2215, 2218, 2227, 2228, 2232, 2234, 2237, 2242, 2246, 2247, 2257, 2272, 2279, 2288, 2292, 2293, 2295, 2298, 2303, 2318, 2322, 2333, 2340, 2341, 2342, 2349, 2353, 2355, 2356, 2358, 2359, 2364, 2365, 2379, 2381, 2385, 2394, 2402, 2403, 2404, 2405, 2406, 2407, 2410, 2413, 2414, 2416, 2419, 2424, 2426, 2429, 2430, 2431, 2442, 2445, 2456, 2460, 2463, 2471, 2473, 2474, 2477, 2480, 2484, 2485, 2487, 2488, 2502, 2506, 2517, 2518, 2521, 2524, 2532, 2534, 2538, 2541, 2544, 2545, 2548, 2549, 2563, 2564, 2568, 2569, 2579, 2580, 2581, 2582, 2585, 2593, 2594, 2595, 2599, 2602, 2603, 2604, 2605, 2610, 2615, 2629, 2630, 2641, 2646, 2647, 2648, 2649, 2650, 2651, 2654, 2655, 2660, 2662, 2663, 2664, 2671, 2687, 2691, 2709, 2710, 2711, 2712, 2715, 2721, 2748, 2799, 2809, 2812, 2858, 2873, 2874, 2919, 2935, 2981, 2997, 3059, 3104, 3105, 3121, 3164, 3181, 3228, 3242, 3288, 3303, 3348, 3349, 3363, 3409, 3412, 3425, 3472, 3473, 3486, 3487, 3488});
            std::sort(simulator.specialParticles.rbegin(), simulator.specialParticles.rend());

            simulator.addPotential(source(-35000, sf::Vector2f(width/2.0f, height)));
            simulator.addParticlePointDrain(20.0, sf::Vector2f(width/2.0f, height));
            simulator.addParticleLineSource(0.4, 15, sf::Vector2f(0,0), sf::Vector2f(0, height));
            simulator.addParticleLineSource(0.4, 31, sf::Vector2f(0,0), sf::Vector2f(width, 0));
            simulator.addParticleLineSource(0.4, 15, sf::Vector2f(width,0), sf::Vector2f(width, height));
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
    sf::RenderWindow window({width, height}, "Flower", sf::Style::Default, settings);
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
    printf("Particle count: %i\n", (int)fs.particles.size());
    // Run while window is open
    while (window.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
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