#include <SFML/GpuPreference.hpp>
#include <SFML/Graphics.hpp>
#include "FieldState.hpp"
#include "FluidParticle.hpp"

using namespace std;

class Renderer{
    public:
        Renderer(sf::RenderWindow& win, float stepsize, FieldState stateobj);
        void render(float delta_t);
    private:
        sf::RenderWindow& window;
        float stepsize;
        int epochs = 1;
        FieldState state;
        FieldState prevState;
};

Renderer::Renderer(sf::RenderWindow& win, float stepsize, FieldState stateobj): window(win), stepsize(stepsize), state(stateobj){
    for (FluidParticle particle : state.particles){
        sf::CircleShape circle(2);
        circle.setFillColor(sf::Color(40, 40, 40));
        circle.setPosition(particle.pos);
        win.draw(circle);
    }

    prevState = state;
}

void Renderer::render(float delta){
    
}