#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define TIMESTEP 0.01
#define SPEED 1/TIMESTEP
#define PI 3.14F

#ifndef VEHICLE_H
#define VEHICLE_H

typedef enum {
    CAR1,
    CAR2,
    CAR3,
    CAR4,
    CAR5,
    CAR6,
    BUS
} tVehicleType; //Vehicle types

class Vehicle
{
protected:
    float x, y;
    float dir;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    virtual void move() = 0; //Pure virtual move function that was implemented in car and bus
    virtual void move2() = 0;
};

#endif // VEHICLE_H
