#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

struct Point {
    double x, y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

void init();
void loop();
void draw();
void events();
short sign(float);
float fun(float, float);
void drawLine(int x1, int y1, int x2, int y2);


sf::RenderWindow* window;
sf::RectangleShape* pixel;

int plotSize[2];
int pixelSize = 2;
float widthFactor = 0;
float heightFactor = 0;
Point* zeroPoint;



int main() {

    init();

    loop();

    return 0;
}

void init() {
    window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Plotter");

    pixel = new sf::RectangleShape;

    plotSize[0] = 20; // X-Axis
    plotSize[1] = 20; // Y-Axis

    pixelSize = 5; // Size of a virtualPixel


    widthFactor = (float)window->getSize().x / ((float)plotSize[0]);
    heightFactor = (float)window->getSize().y / ((float)plotSize[1]);

    zeroPoint = new Point((double)window->getSize().x / 2 + 179, (double)window->getSize().y / 2 + 188);
}

void loop() {

    while (window->isOpen()) {

        widthFactor = (float)window->getSize().x / ((float)plotSize[0]);
        heightFactor = (float)window->getSize().y / ((float)plotSize[1]);

        events();
        draw();

    }

}

void draw() {
    window->clear(sf::Color::White);

    // DRAW X AND Y AXIS

    drawLine(0, zeroPoint->y - 1, window->getSize().x, zeroPoint->y + 1);  // X-Axis
    drawLine(zeroPoint->x - 1, 0, zeroPoint->x + 1, (int)window->getSize().y); // Y-Axis

    // DRAW X AND Y POINTS ON AXES
    pixel->setFillColor(sf::Color::Black);
    pixel->setSize({ 4, 8 });
    for (int i = zeroPoint->x; i > 0; i -= widthFactor) {                                     // X-Points (left to (0,0))
        pixel->setPosition(i - 2, zeroPoint->y - 4);
        window->draw(*pixel);
    }
    for (int i = zeroPoint->x + widthFactor; i < (int)window->getSize().x; i += widthFactor) {// X-Points (right to (0,0))
        pixel->setPosition(i - 2, zeroPoint->y - 4);
        window->draw(*pixel);
    }

    pixel->setSize({ 8, 4 });
    for (int i = zeroPoint->y; i > 0; i -= heightFactor) {                                      // Y-Points (above (0,0))
        pixel->setPosition(zeroPoint->x - 4, i - 2);
        window->draw(*pixel);
    }
    for (int i = zeroPoint->y + heightFactor; i < (int)window->getSize().y; i += heightFactor) {// Y-Points (below (0,0))
        pixel->setPosition(zeroPoint->x - 4, i - 2);
        window->draw(*pixel);
    }

    // DRAW GRAPH
    pixel->setSize({ (float)pixelSize, (float)pixelSize });
    pixel->setFillColor(sf::Color::Blue);

    int w = (int)window->getSize().x;
    int h = (int)window->getSize().y;

    for (int x = 0; x < w; x += (pixelSize - 1)) { // 

        float kx = (x - zeroPoint->x) / widthFactor;

        for (int y = 0; y < h; y += (pixelSize - 1)) {

            float ky = (zeroPoint->y - y) / heightFactor + 1;

            float result = sign(fun(ky - 1 / heightFactor, kx - 1 / widthFactor)) + sign(fun(ky - 1 / heightFactor, kx)) + sign(fun(ky, kx - 1 / widthFactor)) + sign(fun(ky, kx));

            if (result > -4 && result < 4) {

                pixel->setPosition(x, y);

                window->draw(*pixel);

            }

        }


    }


    window->display();
}

void drawLine(int x1, int y1, int x2, int y2) {

    pixel->setPosition(x1, y1);
    pixel->setSize({ (float)x2 - x1,(float)y2 - y1 });
    pixel->setFillColor(sf::Color::Black);

    window->draw(*pixel);

}

void events() {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        double x, y;
        x = sf::Mouse::getPosition(*window).x;
        y = sf::Mouse::getPosition(*window).y;

        zeroPoint->x = x;
        zeroPoint->y = y;


    }

    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheel.x > 0) {
                if (plotSize[0] > 2) {
                    plotSize[0] -= 2;
                }
                if (plotSize[1] > 2) {
                    plotSize[1] -= 2;
                }
            }
            else {
                plotSize[0] += 2;
                plotSize[1] += 2;
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                zeroPoint->x += 50;
            }
            if (event.key.code == sf::Keyboard::Right) {
                zeroPoint->x -= 50;
            }

            if (event.key.code == sf::Keyboard::Up) {
                zeroPoint->y += 50;
            }
            if (event.key.code == sf::Keyboard::Down) {
                zeroPoint->y -= 50;
            }

            if (event.key.code == sf::Keyboard::A) {
                if (plotSize[0] > 2) {
                    plotSize[0] -= 2;
                }
            }
            if (event.key.code == sf::Keyboard::W) {
                if (plotSize[1] > 2) {
                    plotSize[1] -= 2;
                }
            }
            if (event.key.code == sf::Keyboard::D) {
                plotSize[0] += 2;
            }
            if (event.key.code == sf::Keyboard::S) {
                plotSize[1] += 2;
            }
            if (event.key.code == sf::Keyboard::F) {
                pixelSize++;
            }
            if (event.key.code == sf::Keyboard::R) {
                if (pixelSize > 2) {
                    pixelSize--;
                }
            }
        }
    }
}

short sign(float x) {
    return (x > 1) - (x < 1);
}

float fun(float y, float x) {
    return y - cos(x);
}