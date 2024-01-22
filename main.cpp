#include <SFML/Graphics.hpp>
#include <string>

#include "Game.hpp"
#include "Mandelbrot.hpp"

int main() {
    int windowWidth(1200);
    int windowHeight(800);
    std::string title = "Mandelbrot Set";    
    Game game(windowWidth, windowHeight, title);
    game.run();
    return 0;
}