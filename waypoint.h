#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "roadtile.h"

#ifndef WAYPOINT_H
#define WAYPOINT_H

typedef enum {
    DOWN = 1,
    LEFT = 2,
    UP = 3,
    RIGHT = 4
} tWaypointDir;

class Waypoint
{
    float x, y;
    int dir;
    int next1, next2, next3;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    friend class Car;
    //Display waypoints
    Waypoint(tWaypointDir dir, tRoadTileType type, int row, int col, int idx, int next1, int next2, int next3);
    int getNext(); //Get next waypoint randomly

    //Gets position of waypoints
    void getPosition(float &x, float &y, float &dir) const { x = this->x; y = this->y; dir = this->dir; }

    //Sets position of waypoints
    void setPosition(float x, float y, float dir) { this->x = x; this->y = y; this->dir = dir; }
    void draw(sf::RenderWindow *window) {window->draw(sprite);}
};

#endif // WAYPOINT_H
