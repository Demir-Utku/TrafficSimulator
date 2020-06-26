#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>						//Needed libraries for project

#include "roadtile.h"
#include "trafficlightgroup.h"
#include "bus.h"
#include "car.h"
#include "busstop.h"

#define WIDTH 1200
#define HEIGHT 1200

using namespace std;

int main()
{
    float x, y, dir;
    vector<int> stops{};

    //Creating window and setting its size and position
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Traffic Simulator");
    window.setSize(sf::Vector2u(WIDTH / 2, WIDTH / 2));
    window.setPosition(sf::Vector2i(10, 10));

    //Creating roadtiles
    RoadTile roadtiles[] = { {CTL, 0, 0}, {HOR, 0, 1}, {TTOP, 0, 2}, {HOR, 0, 3}, {CTR, 0, 4},
                                 {VER, 1, 0}, {VER, 1, 2} , {VER, 1, 4},
                                 {TLEFT, 2, 0}, {HOR, 2, 1}, {CROSS, 2, 2}, {HOR, 2, 3}, {TRIGHT, 2, 4},
                                 {VER, 3, 0}, {VER, 3, 2} , {VER, 3, 4},
                                 {CBL, 4, 0}, {HOR, 4, 1}, {TBOT, 4, 2}, {HOR, 4, 3}, {CBR, 4, 4} };

    //Creating waypoints
    Waypoint waypoints[] = {
        {UP, CTL, 0, 0, 0, 1, -1, -1}, {RIGHT, CTL, 0, 0, 1, 0, -1, -1},
        {RIGHT, HOR, 0, 1, 0, 3, -1, -1}, {RIGHT, HOR, 0, 1, 1, 2, -1, -1},
        {RIGHT, TTOP, 0, 2, 0, 5, 6, -1}, {DOWN, TTOP, 0, 2, 1, 4, 6, -1},
        {RIGHT, TTOP, 0, 2, 2, 4, 5, -1}, {RIGHT, HOR, 0, 3, 0, 8, -1, -1},
        {RIGHT, HOR, 0, 3, 1, 7, -1, -1}, {RIGHT, CTR, 0, 4, 0, 10, -1, -1},
        {DOWN, CTR, 0, 4, 1, 9, -1, -1}, {DOWN, VER, 1, 4, 0, 12, -1, -1},
        {DOWN, VER, 1, 4, 1, 11, -1, -1}, {DOWN, TRIGHT, 2, 4, 0, 14, 15, -1},
        {LEFT, TRIGHT, 2, 4, 1, 13, 15, -1}, {UP, TRIGHT, 2, 4, 2, 13, 14, -1},
        {UP, VER, 3, 4, 0, 17, -1, -1}, {UP, VER, 3, 4, 1, 16, -1, -1},
        {RIGHT, CBR, 4, 4, 0, 19, -1, -1}, {UP, CBR, 4, 4, 1, 18, -1, -1},
        {RIGHT, HOR, 4, 3, 0, 21, -1, -1}, {RIGHT, HOR, 4, 3, 1, 20, -1, -1},
        {LEFT, TBOT, 4, 2, 0, 23, 24, -1}, {DOWN, TBOT, 4, 2, 1, 22, 24, -1},
        {RIGHT, TBOT, 4, 2, 2, 22, 23, -1}, {LEFT, HOR, 4, 1, 0, 26, -1, -1},
        {LEFT, HOR, 4, 1, 1, 25, -1, -1}, {UP, CBL, 4, 0, 0, 28, -1, -1},
        {LEFT, CBL, 4, 0, 1, 27, -1, -1}, {UP, VER, 3, 0, 0, 30, -1, -1},
        {UP, VER, 3, 0, 1, 29, -1, -1}, {UP, TLEFT, 2, 0, 0, 32, 33, -1},
        {RIGHT, TLEFT, 2, 0, 1, 31, 33, -1}, {UP, TLEFT, 2, 0, 2, 31, 32, -1},
        {UP, VER, 1, 0, 0, 35, -1, -1}, {UP, VER, 1, 0, 1, 34, -1, -1},
        {RIGHT, HOR, 2, 1, 0, 37, -1, -1}, {RIGHT, HOR, 2, 1, 1, 36, -1, -1},
        {RIGHT, CROSS, 2, 2, 0, 39, 40, 41}, {DOWN, CROSS, 2, 2, 1, 38, 40, 41},
        {LEFT, CROSS, 2, 2, 2, 38, 39, 41}, {DOWN, CROSS, 2, 2, 3, 38, 39, 40},
        {LEFT, HOR, 2, 3, 0, 43, -1, -1}, {LEFT, HOR, 2, 3, 1, 42, -1, -1},
        {DOWN, VER, 1, 2, 0, 45, -1, -1}, {DOWN, VER, 1, 2, 1, 44, -1, -1},
        {DOWN, VER, 3, 2, 0, 47, -1, -1}, {DOWN, VER, 3, 2, 1, 46, -1, -1}
    };

    //Traffic lights
    TrafficLight tlights[] = {
        {2*239 + 70, 250, 180, GREEN}, {2*239 + 240, 170, 90, RED},
        {4*239 + 70, 2*239 + 70, 180, RED}, {4*239 + 50, 2*239 + 170, 0, GREEN},
        {2*239 + 40, 2*239 + 170, 90, GREEN}, {2*239 + 70, 2*239 + 70, 180, RED},
        {2*239 + 200, 2*239 + 70, 270, RED}
    };

    TrafficLightGroup tlg1{10};     tlg1.add(&tlights[0]);      tlg1.add(&tlights[1]);
    TrafficLightGroup tlg2{10};     tlg2.add(&tlights[2]);      tlg2.add(&tlights[3]);
    TrafficLightGroup tlg3{10};     tlg3.add(&tlights[4]);      tlg3.add(&tlights[5]);      tlg3.add(&tlights[6]);

    //Bus stops that buses have to move through them
    BusStop busstops[] = {
        {239 * 1 + 50, 175, 90}, {239 * 3 + 50, 175, 90}, {239 * 4 + 60, 239 * 1 + 50, 180},
        {239 * 2 + 60, 239 * 2 + 300, 180}, {180, 239 * 3 + 100, 0}
    };

    waypoints[0].getPosition(x, y, dir);
    Car car(CAR1, x, y, dir); //Sets car's position

    waypoints[1].getPosition(x, y, dir);
    Car car2(CAR2, x, y, dir); //Sets car2's position

    waypoints[3].getPosition(x, y, dir);
    Bus bus(BUS, x, y, dir, stops);
    bus.addStop(1);
    bus.addStop(2);
    bus.addStop(3);
    bus.addStop(4);
    bus.addStop(5); //Adding bus stops to bus

    waypoints[6].getPosition(x, y, dir);
    Bus bus2(BUS, x, y, dir, stops);
    bus2.addStop(1);
    bus2.addStop(2);
    bus2.addStop(3);
    bus2.addStop(4);
    bus2.addStop(5);

    waypoints[5].getPosition(x, y, dir);
    Car car3(CAR3, x, y, dir);

    waypoints[8].getPosition(x, y, dir);
    Car car4(CAR4, x, y, dir);

    waypoints[42].getPosition(x, y, dir);
    Car car5(CAR5, x, y, dir);

    waypoints[31].getPosition(x, y, dir);
    Car car6(CAR6, x, y, dir);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < sizeof(roadtiles) / sizeof(RoadTile); i++) {
            roadtiles[i].draw(&window); //Drawing roadtiles
        }

        for (int i = 0; i < sizeof(waypoints) / sizeof(Waypoint); i++) {
            waypoints[i].draw(&window); //Drawing waypoints
        }

        for(int i = 0; i < sizeof (busstops) / sizeof (BusStop); i++)
            busstops[i].draw(&window); //Drawing stops

        for (int i = 0; i < sizeof(tlights) / sizeof(TrafficLight); i++) {
            tlights[i].draw(&window); //Drawing t lights
        }

        //Drawing cars and buses
        car.draw(&window);
        car2.draw(&window);
        bus.draw(&window);
        car3.draw(&window);
        bus2.draw(&window);
        car4.draw(&window);
        car5.draw(&window);
        car6.draw(&window);

        //Moving cars and buses
        car.move();
        car2.move2();
        bus.move();
        bus2.move();
        car3.move2();
        car4.move();
        car5.move();
        car6.move();

        //Stopping vehicles at t lights position when state is RED
        for(int i = 0; i < 7; i++) {
            car.redLight(&tlights[i], x, y, dir);
            car2.redLight(&tlights[i], x, y, dir);
            car3.redLight(&tlights[i], x, y, dir);
            car4.redLight(&tlights[i], x, y, dir);
            car5.redLight(&tlights[i], x, y, dir);
            car6.redLight(&tlights[i], x, y, dir);
            bus.redLight(&tlights[i], x, y, dir);
            bus2.redLight(&tlights[i], x, y, dir);
        }

        //Simulate tlights group
        tlg1.simulate(10);
        tlg2.simulate(10);
        tlg3.simulate(10);


        window.display();

        sf::sleep(sf::seconds(0.01));
    }

    return 0;
}
