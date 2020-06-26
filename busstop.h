#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef BUSSTOP_H
#define BUSSTOP_H

class BusStop
{
    float x; //x coordinate of the bus stop
    float y; //y coordinate of the bus stop
    float dir; //direction (orientation) of the bus stop
    sf::Texture texture;
    sf::Sprite sprite;

public:
    BusStop(float x, float y, float dir) {
        this->x = x; this->y = y; this->dir = dir; //Initialization of the variables
        texture.loadFromFile("images/busstop/busstop.png"); //Loading the texture.
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(x, y)); //Setting the position of the sprite
        sprite.setRotation(dir); //Setting the orientation of the sprite
        sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
    }
    //Function for getting the position and rotation of the bus stop
    void getPosition(float &x, float &y, float &dir) {x = this->x; y = this->y; dir = this->dir;}

    //Draws the busstop sprite to the window
    void draw(sf::RenderWindow *window) {window->draw(this->sprite);}
};

#endif // BUSSTOP_H
