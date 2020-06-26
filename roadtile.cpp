#include "roadtile.h"

//Constructor for RoadTile class
RoadTile::RoadTile(tRoadTileType t, int row, int col) {
    this->x = col * TILEWIDTH; //Since every roadtile is 239x239, we converted coordinates to column/row number * 239
    this->y = row * TILEHEIGHT;

    //Loading the textures for different types of roadtiles
    switch (t) {
        case CTL: //Corner top left
            texture.loadFromFile("images/roadpieces/corner-topleft.png");
            break;
        case TTOP: // T junction at top, etc..
            texture.loadFromFile("images/roadpieces/t-top.png");
            break;
        case CTR:
            texture.loadFromFile("images/roadpieces/corner-topright.png");
            break;
        case TLEFT:
            texture.loadFromFile("images/roadpieces/t-left.png");
            break;
        case CROSS:
            texture.loadFromFile("images/roadpieces/cross.png");
            break;
        case TRIGHT:
            texture.loadFromFile("images/roadpieces/t-right.png");
            break;
        case CBL:
            texture.loadFromFile("images/roadpieces/corner-bottomleft.png");
            break;
        case TBOT:
            texture.loadFromFile("images/roadpieces/t-bottom.png");
            break;
        case CBR:
            texture.loadFromFile("images/roadpieces/corner-bottomright.png");
            break;
        case HOR:
            texture.loadFromFile("images/roadpieces/straight-horizontal.png");
            break;
        case VER:
            texture.loadFromFile("images/roadpieces/straight-vertical.png");
            break;
        case NONE:
            break;
    }
    sprite.setTexture(texture); //Setting the texture to the sprite
    sprite.setPosition(sf::Vector2f(this->x, this->y)); //Setting the position of the roadtile sprite
}
