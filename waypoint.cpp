#include "waypoint.h"

Waypoint::Waypoint(tWaypointDir dir, tRoadTileType type, int row, int col, int idx, int next1, int next2, int next3)
{
    //Initialization of variables
    this->x = col * 239;
    this->y = row * 239;
    this->dir = dir;
    this->next1 = next1;
    this->next2 = next2;
    this->next3 = next3;

    //Giving the offsets to the roadtiles to draw waypoints
    switch (type) {
        case CTL:
            this->x += (idx == 0) ? 118 : 218;
            this->y += (idx == 0) ? 218 : 121;
            break;
        case TTOP:
            if(idx == 0){
                this->x += 20;
                this->y += 121;
            }
            else if(idx == 1){
                this->x += 118;
                this->y += 218;
            }
            else{
                this->x += 218;
                this->y += 121;
            }
            break;
        case CTR:
            this->x += (idx == 0) ? 20 : 118;
            this->y += (idx == 0) ? 121 : 218;
            break;
        case TLEFT:
            if(idx == 0){
                this->x += 118;
                this->y += 20;
            }
            else if(idx == 1){
                this->x += 218;
                this->y += 121;
            }
            else{
                this->x += 118;
                this->y += 218;
            }
            break;
        case CROSS:
            if(idx == 0){
                this->x += 20;
                this->y += 121;
            }
            else if(idx == 1){
                this->x += 118;
                this->y += 20;
            }
            else if(idx == 2){
                this->x += 218;
                this->y += 121;
            }
            else{
                this->x += 118;
                this->y += 218;
            }
            break;
        case TRIGHT:
            if(idx == 0){
                this->x += 118;
                this->y += 20;
            }
            else if(idx == 1){
                this->x += 20;
                this->y += 121;
            }
            else{
                this->x += 118;
                this->y += 218;
            }
            break;
        case CBL:
            this->x += (idx == 0) ? 118 : 218;
            this->y += (idx == 0) ? 20 : 121;
            break;
        case TBOT:
            if(idx == 0){
                this->x += 20;
                this->y += 121;
            }
            else if(idx == 1){
                this->x += 118;
                this->y += 20;
            }
            else{
                this->x += 218;
                this->y += 121;
            }
            break;
        case CBR:
            this->x += (idx == 0) ? 20 : 118;
            this->y += (idx == 0) ? 121 : 20;
            break;
        case HOR:
            this->x += (idx == 0) ? 20: 172;
            this->y += 121;
            break;
        case VER:
            this->x += 118;
            this->y += (idx == 0) ? 20 : 172;
            break;
        default:
            break;
    }

    //Loading waypoints' textures
    switch (dir) {
        case UP:
            texture.loadFromFile("images/waypoints/up.png");
            break;
        case DOWN:
            texture.loadFromFile("images/waypoints/down.png");
            break;
        case LEFT:
            texture.loadFromFile("images/waypoints/left.png");
            break;
        case RIGHT:
            texture.loadFromFile("images/waypoints/right.png");
            break;
    }
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(this->x, this->y));
}

//Randomly get next waypoint
int Waypoint::getNext()
{
    if(next2 == -1 && next3 == -1 && next1 != -1) {
        return next1; //The case when roadtiles have 2 waypoints
    }

    else if(next3 == -1 && next1 != -1 && next2 != -1) {
        int select2[2] = {next1, next2};
        srand( (unsigned)time(NULL) );
        return select2[rand() % 2]; //The case when roadtiles have 3 waypoints
    }

    else if(next1 != -1 && next2 != -1 && next3 != -1) {
        int select3[3] = {next1, next2, next3};
        srand( (unsigned)time(NULL) );
        return select3[rand() % 3]; //The case when roadtiles have 4 waypoints
    }
    else
        return -1;
}
