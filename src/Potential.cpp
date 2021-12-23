// May not be needed
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <utility>
class Potential{
    public:
        explicit Potential(std::function<float(sf::Vector2f)> pot);
    private:
        std::function<float(sf::Vector2f)> value;
};

Potential::Potential(std::function<float(sf::Vector2f)> pot) : value(std::move(pot)){
    
}