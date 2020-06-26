#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define TILEWIDTH 239
#define TILEHEIGHT 239

#ifndef ROADTILE_H
#define ROADTILE_H

typedef enum {
    NONE = 0,
    HOR,
    VER,
    TTOP,
    TBOT,
    TLEFT,
    TRIGHT,
    CTL,
    CTR,
    CBL,
    CBR,
    CROSS
} tRoadTileType; //Road tile types

class RoadTile
{
    float x, y; //Coordinates
    sf::Texture texture;
    sf::Sprite sprite;
public:
    RoadTile(tRoadTileType t, int row, int col); //RoadTile constructor
    void draw(sf::RenderWindow *window) {window->draw(sprite);} //Drawing the roadtile sprite to the window.
};

#endif // ROADTILE_H
