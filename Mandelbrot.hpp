#ifndef __MANDELBROT_HPP__
#define __MANDELBROT_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class Mandelbrot : public sf::Drawable, public sf::Transformable {
    public: 
    Mandelbrot(int numRows, int numCols, int maxNumIter, double minRe, double maxRe, double minIm, double maxIm);

    void zoom(const double z, const int mouseX, const int mouseY);
    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
    void setMaxIter(const std::function<int(int)>& f);
    void compute();

    private:
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    

    const int width; 
    const int height; 

    int maxIter; 

    double minReal; 
    double maxReal; 
    double minImag;
    double maxImag;

    static const std::vector<sf::Color> palette;
};

#endif