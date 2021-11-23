#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

void init(); 
void loop(); 
void draw(); 
void events();
double fun(double); 
void drawLine(int x1, int y1, int x2, int y2); 


sf::RenderWindow *window;
sf::RectangleShape *pixel;

int plotSize[2];
int pixelSize = 2; 
double widthFactor = 0; 
double heightFactor = 0; 

int main(){

    init(); 

    loop(); 

    return 0;
}

void init() {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Plotter");

    pixel = new sf::RectangleShape; 
    (*pixel).setSize({ 1, 1 }); 
    (*pixel).setFillColor(sf::Color::Black);

    plotSize[0] = 20; // X-Axis
    plotSize[1] = 20; // Y-Axis

    pixelSize = 2; // Size of a virtualPixel


    widthFactor = (double)window->getSize().x / ((double)plotSize[0]);
    heightFactor = (double)window->getSize().y / ((double)plotSize[1]);

}

void loop() {

    while (window->isOpen()) {

        events(); 
        draw(); 

    }

}

void draw() {
    window->clear(sf::Color::White); 

    // DRAW X AND Y AXIS

    drawLine(0, window->getSize().y / 2 - 1, window->getSize().x, window->getSize().y / 2 + 1);  // X-Axis
    drawLine((int)window->getSize().x / 2 - 1, 0, (int)window->getSize().x / 2 + 1, (int)window->getSize().y); // Y-Axis

    // DRAW X AND Y POINTS ON AXES
    pixel->setFillColor(sf::Color::Black);
    pixel->setSize({ 4, 8 });
    for (int i = -plotSize[0] / 2; i <= plotSize[0] / 2; i++) {
        pixel->setPosition(i * widthFactor + window->getSize().x / 2 - 2, window->getSize().y / 2 - 4);
        window->draw(*pixel);
    }

    pixel->setSize({ 8, 4 });
    for (int i = -plotSize[1] / 2; i <= plotSize[1] / 2; i++) {
        pixel->setPosition(window->getSize().x / 2 - 4, i * heightFactor + window->getSize().y / 2 - 2);
        window->draw(*pixel);
    }

    // DRAW GRAP
    pixel->setSize({ (float)pixelSize, (float)pixelSize });
    pixel->setFillColor(sf::Color::Blue); 


    for (double x = -((int)window->getSize().x / 2); x < ((int)window->getSize().x / 2); x += 1) { // 2 is the dimension of a pixel (1vpx = 2*2 px) 

        double kx = x / widthFactor;
        double ky = fun(kx); 
        double finalY = (int)window->getSize().y / 2 - ky * heightFactor - pixelSize / 2; 
        double finalX = widthFactor * kx + (int)window->getSize().x / 2 - pixelSize / 2;

        pixel->setPosition(finalX, finalY);

        window->draw(*pixel); 
    }

    window->display(); 
}

void drawLine(int x1, int y1, int x2, int y2) {

    pixel->setPosition(x1, y1); 
    pixel->setSize({(float) x2 - x1,(float) y2 - y1 });
    pixel->setFillColor(sf::Color::Black); 

    window->draw(*pixel); 

}

void events() {
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

double fun(double x) {
    return  x*x*x -2 * x*x;
}