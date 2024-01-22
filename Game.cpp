#include "Game.hpp"

#include <iostream>

Game::Game(int width, 
           int height, 
           const std::string& title):
            window(sf::VideoMode(width, height), title),
            mandelbrot(width, height, 256, -2.0, 1.0, -1.0, 1.0) {
                //window.setFramerateLimit(60);
            } 

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
    
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                mandelbrot.zoom(5, event.mouseButton.x, event.mouseButton.y);
            }
            if (event.mouseButton.button == sf::Mouse::Right) {
                mandelbrot.zoom(1.0 / 5, event.mouseButton.x, event.mouseButton.y);
            }
        }
        
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                if (event.mouseWheelScroll.delta > 0) {
                    auto f = [](int val) {return val * 2;};
                    mandelbrot.setMaxIter(f);
                }
                else {
                    auto f = [](int val) {return val / 2;};
                    mandelbrot.setMaxIter(f);
                }
            }
        }
    }
}

void Game::update() {
    mandelbrot.compute();
}

void Game::render() {
    window.clear();
    window.draw(mandelbrot);
    window.display();
}