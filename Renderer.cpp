#include <SFML/GpuPreference.hpp>
#include <SFML/Graphics.hpp>
#include "FieldState.cpp"

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
};

Renderer::Renderer(sf::RenderWindow& win, float stepsize, FieldState stateobj): window(win), stepsize(stepsize), state(stateobj){
}

void Renderer::render(float delta){
    
}