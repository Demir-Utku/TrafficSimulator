#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

typedef enum {
    GREEN = 0,
    RED = 1
}tLightState; //Traffic Light state. red or green light

class TrafficLight {
    float x, y; // Coordinates for traffic lights
    float dir; //direction of the traffic light (determines the orientation of the traffic light on the map)
    tLightState state; //current state of the light (either green or red). tLightState should be an enum
    TrafficLight* next; //pointer to the next traffic light in the traffic light group
    sf::Texture redTexture; //texture for red light
    sf::Texture greenTexture; //texture for green light
    sf::Sprite sprite;

public:
    //TrafficLight class constructor
    //x: x coordinate of the traffic light
    //y: y coordinate of the traffic light
    //dir: traffic light direction, i.e., orientation
    //state: initial state of the traffic light
    TrafficLight(float x, float y,  float dir, tLightState state)
    {
        this->x=x;
        this->y=y;
        this->dir=dir;
        //Initialization of variables (coordiates and rotation)

        //in case of green light
        if(state == GREEN){
            greenTexture.loadFromFile("images/trafficlights/green.png");
            sprite.setTexture(greenTexture);
        }

        //in case of red light
        else{
            redTexture.loadFromFile("images/trafficlights/red.png");
            sprite.setTexture(redTexture);
        }

        sprite.setPosition(sf::Vector2f(x,y));
        sprite.setRotation(dir);
        sprite.setOrigin(0, 0);
    }

    void setNext(TrafficLight *next) {
        this->next = next;
    }

    TrafficLight * returnNext() { return next; }

    //Returns the position and the direction of the traffic light
    //dir: orientation
    void getPosition(float &x, float &y, float &dir) {x = this->x; y = this->y; dir = this->dir;}

    //Draws the traffic lights to the window
    void draw(sf::RenderWindow *window) {window->draw(this->sprite);}

    //Returns current traffic light state
    tLightState getState() {return state;}

    //Sets the traffic light state and loads the textures again in case of change in the states
    void setState(tLightState state) {
        this->state = state;

        if(state == GREEN) {
            greenTexture.loadFromFile("images/trafficlights/green.png");
            sprite.setTexture(greenTexture);
        }
        else {
            redTexture.loadFromFile("images/trafficlights/red.png");
            sprite.setTexture(redTexture);
        }
    }
};

#endif // TRAFFICLIGHT_H
