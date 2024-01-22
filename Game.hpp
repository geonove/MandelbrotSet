#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/Graphics.hpp>

#include "Mandelbrot.hpp"

class Game {
    public: 
    Game(int width, 
         int height,
         const std::string& title);

    void run();

    private: 
    // Window
    sf::RenderWindow window;
    // Mandelbrot
    Mandelbrot mandelbrot;
    // Clock to compute frame rate
    sf::Clock clock;

    void processEvents();
    void update();
    void render();    
};

#endif