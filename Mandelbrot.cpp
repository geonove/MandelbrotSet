#include "Mandelbrot.hpp"

#include <cmath>
#include <iostream>

sf::Color linear_interpolation(const sf::Color& v, const sf::Color& u, double a)
{
	auto const b = 1 - a;
	return sf::Color(b*v.r + a * u.r, b*v.g + a * u.g, b*v.b + a * u.b);
}

const std::vector<sf::Color> Mandelbrot::palette = {
    {0, 0, 0},        // Black for points within the set
    {0, 0, 255},      // Blue
    {255, 255, 0},    // Yellow
    {0, 255, 0},      // Green
    {0, 255, 255},    // Cyan
    {255, 0, 0},      // Red
    {255, 0, 255},    // Magenta
    {255, 255, 255}   // White for points that escape quickly
};

Mandelbrot::Mandelbrot(int W, int H, int maxNumIter, double minRe, double maxRe, double minIm, double maxIm) : 
        image(),
        width(W),
        height(H), 
        maxIter(maxNumIter),
        minReal(minRe),
        maxReal(maxRe),
        minImag(minIm),
        maxImag(maxIm) {
            image.create(width, height);
        };

void Mandelbrot::compute() {
    //sf::Clock clock;
    //clock.restart();
    #pragma omp parallel for
    for (int y = 0; y < height; y++) {
        #pragma omp parallel for
        for (int x = 0; x < width; x++) {
            double currReal = minReal + (maxReal - minReal) * x / width;
            double currImag = minImag + (maxImag - minImag) * y / height;

            double real = 0.0, imag = 0.0;
            double real2 = 0.0, imag2 = 0.0;            
            double w = 0.0; 

            int iter = 0; 
           
            while (real2 + imag2 <= 4 && iter < maxIter) {
                real = real2 - imag2 + currReal;
                imag = w - real2 - imag2 + currImag;
                real2 = real * real;
                imag2 = imag * imag;
                w = (real + imag) * (real + imag);
                iter++;
            }

            int r = 1.0 * (maxIter - iter) / maxIter * 0xff;
			int g = r, b = r;

            static const auto maxColor = palette.size() - 1;
			if (iter == maxIter)
                iter = 0;
			double mu = 1.0 * iter / maxIter;
			//scale mu to be in the range of colors
			mu *= maxColor;
			auto i_mu = static_cast<size_t>(mu);
			auto color1 = palette[i_mu];
			auto color2 = palette[std::min(i_mu + 1, maxColor)];
			sf::Color c = linear_interpolation(color1, color2, mu - i_mu);

            image.setPixel(x, y, c);
        }
    }
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    //std::cout << clock.getElapsedTime().asSeconds() << std::endl;
}

void Mandelbrot::zoom(const double z, const int mouseX, const int mouseY) {
   double currReal = minReal + (maxReal - minReal) * mouseX / width;
   double currImag = minImag + (maxImag - minImag) * mouseY / height;

   double tempMinReal = currReal - (maxReal - minReal) / 2 / z; 
   maxReal = currReal + (maxReal - minReal) / 2 / z;
   minReal = tempMinReal;
   
   double tempMinImag = currImag - (maxImag - minImag) / 2 / z;
   maxImag = currImag + (maxImag - minImag) / 2 / z;
   minImag = tempMinImag;
}

void Mandelbrot::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(sprite);
}

void Mandelbrot::setMaxIter(const std::function<int(int)>& f ) {
    maxIter = f(maxIter);
    maxIter = maxIter < 1 ? 1 : maxIter;
    maxIter = maxIter > 2000 ? 2000 : maxIter;
    //std::cout << maxIter << std::endl;
}
