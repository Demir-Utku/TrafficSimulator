#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <math.h>

#include "vehicle.h"
#include "busstop.h"
#include "trafficlight.h"

#ifndef BUS_H
#define BUS_H

class Bus : public Vehicle //Bus class is inherited from Vehicle class
{
    /*
    is a vector of BusStop indexes that the bus will visit in order. When the bus
    reaches the last stop, it should go back to the first element in the vector container
    and should repeat its visits starting from the first bus stop. There should be at
    least 5 bus stops for a bus. Bus stops can be common between the two busses.
    */
    std::vector<int> stops{};
    int currentStop; //Current stop index
public:
    Bus(tVehicleType t, float x, float y, float dir, std::vector<int> stops) {
        //Initialization of the variables.
        this->x = x;
        this->y = y;
        this->dir = dir;
        this->stops = stops;

        if(t == BUS) {
            texture.loadFromFile("images/vehicles/bus.png"); //Loading the bus texture
        }

        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(x, y));
        sprite.setRotation(dir * 90);
        sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
    }

    //This function detects traffic lights at specific position and stop the car at red lights
    void redLight(TrafficLight light[], float &x, float &y, float &dir) {
        float tx, ty, tdir;
        light->getPosition(tx, ty, tdir);

        if(light->getState() == RED) {
            if(x == tx) {
                x = tx;
            }

            if(y == ty) {
                y = ty;
            }
        }

        sprite.setPosition(x, y);
    }

    void move() {
        if(dir == 1) y += 3; //if direction is down, increase y
        if(dir == 2) x -= 3; //if direction is left, decrease x
        if(dir == 3) y -= 3; //if direction is up, decrease y
        if(dir == 4) x += 3; //if direction is right, increase x

        //If x is about at the end of the screen and direction is right, change its direction to down (CTR)
        if(x < 1080 && x >= 1075 && dir == 4) dir = 1;

        //If x is about at the end of the screen, y is at the middle of the screen and direction is down:
        //Change the direction to left (TRIGHT)
        if(x < 1080 && x >= 1075 && y < 605 && y >= 595 && dir == 1) dir = 2;

        //If x and y are at the middle of the screen and direction is left, change the direction to down (CROSS)
        if(x < 605 && x > 595 && y < 605 && y >= 595 && dir == 2) dir = 1;

        //If x is at the middle of the screen, y is nearly at the end of the screen and direction is down:
        //Change the direction to left (TBOT)
        if(x < 605 && x > 595 && y >= 1075 && y < 1080 && dir == 1) dir = 2;

        //If y is nearly at the end of the screen, x is at zeroth column and the direction is left:
        //Change the direction to up (CBL)
        if(y >= 1075 && y < 1080 && x < 130 && x >= 107 && dir == 2) dir = 3;

        //If x and y are at the zeroth column and the direction is up:
        //Change its direction to right (CTL)
        if(x < 130 && x >= 107 && y < 130 && y >= 107 && dir == 3) dir = 4;

        sprite.setPosition(sf::Vector2f(x, y)); //Setting the position of the sprite

        if(dir != 4)
            sprite.setRotation(dir * 90.0f); //Setting the rotation
        else if(dir == 4)
            sprite.setRotation(0.0f); //If direction is right, instead of 360.0f, changed it to 0.0f
    }

    void move2() {
        //This function was added because we wanted to add another movement function for car which is a second option.
        //Therefore, we have to add this move2() function to the Vehicle class as a virtual function.
        //Hence, we have to add this function also in the Bus class.
    }


    // Adds a BusStop index for the bus to stop at
    void addStop(int index) {
        stops.push_back(index); //In vector type variables, to add an index for the bus stop, we used push_back() method.
    }

    void draw(sf::RenderWindow *window) {
        window->draw(this->sprite); //Drawing the bus sprite to the window.
    }
};

#endif // BUS_H
