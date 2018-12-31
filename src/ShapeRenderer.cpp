//
// Created by Marcel on 31/12/2018.
//

#include "ShapeRenderer.hpp"

ShapeRenderer::ShapeRenderer(sf::RenderWindow& win) : window(win) {}

void ShapeRenderer::addShape(sf::Shape* shape) {
    shapes.push_back(shape);
}

void ShapeRenderer::clearAll(){
    shapes.clear();
}

void ShapeRenderer::render() {
    for (sf::Shape* shape : shapes){
        window.draw(*shape);
    }
}