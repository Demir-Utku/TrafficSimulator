#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "vehicle.h"
#include "waypoint.h"
#include "trafficlight.h"

#ifndef CAR_H
#define CAR_H

class Car : public Vehicle { //Car class is inherited from Vehicle class {
public:
    //Constructor for the Car class
    Car(tVehicleType t, float x, float y, float dir) {
        //Initialization of the variables
        this->x = x;
        this->y = y;
        this->dir = dir;

        //Loading the textures according to the vehicle type
        switch (t) {
            case CAR1:
                texture.loadFromFile("images/vehicles/car1.png");
                break;
            case CAR2:
                texture.loadFromFile("images/vehicles/car2.png");
                break;
            case CAR3:
                texture.loadFromFile("images/vehicles/car3.png");
                break;
            case CAR4:
                texture.loadFromFile("images/vehicles/car4.png");
                break;
            case CAR5:
                texture.loadFromFile("images/vehicles/car5.png");
                break;
            case CAR6:
                texture.loadFromFile("images/vehicles/car6.png");
                break;
            default:
                break;
        }

        sprite.setTexture(texture);

        //Sets sprite's origin
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
        //This function includes the first alternative path for cars

        TrafficLight tlights[] = {
            {2*239 + 70, 250, 180, GREEN}, {2*239 + 240, 170, 90, RED},
            {4*239 + 70, 2*239 + 70, 180, RED}, {4*239 + 50, 2*239 + 170, 0, GREEN},
            {2*239 + 40, 2*239 + 170, 90, GREEN}, {2*239 + 70, 2*239 + 70, 180, RED},
            {2*239 + 200, 2*239 + 70, 270, RED}
        };

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
        //This function includes the second alternative path for cars

        //This part is the same as in the first option
        if(dir == 1) y += 3;
        if(dir == 2) x -= 3;
        if(dir == 3) y -= 3;
        if(dir == 4) x += 3;

        //If x is at the middle of the screen, y is at the beginning of the screen, and the direction is right:
        //Change the direction to down (TTOP)
        if(x < 605 && x > 595 && y >= 107 && y < 130 && dir == 4) dir = 1;

        //If x is at the middle of the screen, y is nearly at the end of the screen and the direction is down:
        //Change the direction to left (TBOT)
        if(x < 605 && x > 595 && y >= 1075 && y < 1080 && dir == 1) dir = 2;

        //If y is nearly at the end of the screen, x is at the beginning of the screen and the direction is left:
        //Change the direction to up (CBL)
        if(y >= 1075 && y < 1080 && x < 130 && x >= 107 && dir == 2) dir = 3;

        //If x and y are at the beginning og the screen, and the direction is up
        //Change the direction to right (CTL)
        if(x < 130 && x >= 107 && y < 130 && y >= 107 && dir == 3) dir = 4;

        sprite.setPosition(sf::Vector2f(x, y)); //Set sprite's position

        if(dir != 4)
            sprite.setRotation(dir * 90.0f); //Setting the rotation
        else if(dir == 4)
            sprite.setRotation(0.0f); //If direction is right, changed it to 0.0f instead of 4 * 90.0f = 360.0f
    }

    void draw(sf::RenderWindow *window) {
        window->draw(this->sprite); //Drawing the car sprite to the window.
    }
};

#endif // CAR_H
