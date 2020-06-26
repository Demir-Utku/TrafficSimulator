## TrafficSimulator

### Project Objective

The objective of this project is to implement a traffic simulator using object oriented programming methods. The simulator simulates an urban environment with various vehicles moving in traffic.

The project was implemented using SFML Graphics and Multimedia library. I used some sprite objects which are road pieces, vehicles, way points, traffic lights, and bus stops objects.

### First Part of the Project

In the first phase of the project, I am expected to draw the environment and move a single car around the track.

Simulation has way points that show the points in the track that the car will follow and the direction the car may go.

Every road tile is a 239 by 239 pixel graphic sprite. Each tile has a set of two or more way points on it. Each way point has an internal index starting from 0 within the tile it belongs to as well as internal x-/y- coordinates relative to the top-left corner of the tile. The figure below is just an example of road tiles with way points on it and shows a tile and the way points belonging to it along with the internal way point indexes and their relative coordinates with respect to the top-left corner of the tile.

![Road tile](https://github.com/Demir-Utku/TrafficSimulator/blob/master/waypoints.png)

Classes in the first part:

```
//RoadTile
//Private Members:
float x; //x coordinate of the top left corner of the road tile
float y; //y coordinate of the top left corner of the road tile
sf::Texture texture; //tile texture object
sf::Sprite sprite; //tile sprite object

//Public Methods:
RoadTile (tRoadTileType t, int row, int col);
/*Constructor for the RoadTile class
parameters:
row: Row number for the tile
col: Column number for the tile
t: Tile type (one of the available tile types, such as left t-junction, cross-
junction, top-left corner, etc.)*/

void draw();
//Draws the tile to screen

//Vehicle
//Private Members:
float x;
float y;
float angle;
bool origin_set;
sf::Texture texture; //vehicle texture object
sf::Sprite sprite; //vehicle sprite object

//Public Methods:
Vehicle(tVehicleType t, float x, float y, float angle);
/*Constructor for the Vehicle class
parameters:
t: Vehicle type (one of the available vehicle types)
x: x coordinate of the current vehicle position
y: y coordinate of the current vehicle position
angle: vehicle heading angle, i.e., orientation*/

void move(float &x, float &y, float &angle);
/*Moves the vehicle and draws it to screen at the new location
parameters:
x: x coordinate to move the vehicle to
y: y coordinate to move the vehicle to
angle: new vehicle heading angle after the move.*/

//Waypoint
//Private Members:
float x; //Global x coordinate of the waypoint
float y; //Global y coordinate of the waypoint
int dir; //direction of the waypoint (one of the 4 available directions)
int next1; //Global index of the first alternative next waypoint
int next2; //Global index of the second alternative next waypoint
int next3; //Global index of the third alternative next waypoint
sf::Texture texture; //waypoint texture object
sf::Sprite sprite; //waypoint sprite object

//Public Methods:
Waypoint(tWaypointDir dir, tRoadTileType type, int row, int col, int idx, int next1, int next2, int next3);
/*Waypoint constructor
parameters:
dir: Waypoint direction
type: Road tile type this waypoint belongs to
row: Row number of the tile this waypoint belongs to
col: Column number of the tile this waypoint belongs to
idx: Internal index of the waypoint within the tile it belongs to
next1: Global index of the first alternative next waypoint
next2: Global index of the second alternative next waypoint
next3: Global index of the third alternative next waypoint
*/

int getNext();
//Returns the index of the next waypoint. If there are alternative waypoints, returns the index of one of them randomly.

void getPosition(float &x, float &y, float &dir);
//Returns the x, y coordinates and the direction of the waypoint

void draw();
//Draws the waypoint to the screen
```

### Second Part of the Project

In this second part of the project, I had done the simulation with 6 vehicles.

Classes in the second part:

```
//TrafficLight
//Private Members:
float x; //x coordinate of the traffic light
float y; //y coordinate of the traffic light
float dir; //direction of the traffic light (determines the orientation of the traffic light on the map)
tLightState state; //current state of the light (either green or red). tLightState should be an enum
sf::Texture redTexture; //texture for the traffic light with red turned on
sf::Texture greenTexture; //texture for the traffic light with green turned on
sf::Sprite sprite; //sprite for the traffic light
TrafficLight *next; //pointer to the next traffic light in the traffic light group

//Public Methods
TrafficLight(float x, float y, float dir, tLightState state);
/*Constructor for the traffic light class
parameters:
x: x coordinate of the traffic light
y: y coordinate of the traffic light
dir: traffic light direction, i.e., orientation
state: initial state of the traffic light*/

void getPosition(float &x, float &y, float &dir);
/*Returns the position and the direction of the traffic light
parameters:
x: x coordinate of the traffic light
y: y coordinate of the traffic light
dir: traffic light direction, i.e., orientation*/

void draw();
//Draws the traffic light to screen

tLightState getState();
//Returns the current traffic light state

void setState(tLightState state);
//Sets the traffic light state parameters:
//state: State to set the traffic light to

//TrafficLightGroup
//Private Members:
TrafficLight *head; //Pointer to the head of the traffic light in the group
TrafficLight *greenLight; //Pointer to the current traffic light to be turned to green
float time; //Current time elapsed in seconds
float duration; //Period of switching to the next traffic light to make it green

//Public Methods:
TrafficLightGroup(float duration);
/* TrafficLightGroup constructor
parameters:
duration: TrafficLight switching period*/

void add(TrafficLight *light);
/* Adds a new traffic light to the group
parameters:
light: Pointer to the traffic light object to be added to the group */

void simulate(float timestep);
/* Runs traffic light simulation by advancing the traffic light group timer by timestep
If the traffic light group timer reaches the switching period (i.e., duration member variable) of
the group, the next light in the group is turned into green while the others are turned into red
parameters:
timestep: timestep to be added to the current time */
```

A traffic light group is to be instantiated at every road junction when there is multiple inbound traffic coming to that junction. Within that group, there needs to be a traffic light for each inbound traffic. Traffic lights behave as linked lists.

In each group, there has to be exactly one traffic light in green state, while the other lights must be red. Therefore, traffic is allowed for only one inbound traffic for a particular junction. Traffic lights have two states only: red and green (no yellow state). They face the incoming traffic and are
placed on the right side of the road, so you need to set each light’s position and orientation correctly.

Each group has an associated timer (the time attribute) and a period (the duration attribute) which determine when the next light needs go green within that group. The timer increments by the timestep attribute every time simulate method is called. When the timer reaches the duration value, the next light in the group goes green while the others in the group go red and the timer resets back to zero. Note that each traffic light group needs to be simulated individually.

The cars have the same cruising speed but does not crash into each other. So, they may need to stop occasionally.

### Final Part of the Project

In the final part, I run the simulation with at least 6 cars and at least 2 buses. With 6 cars and 2 buses, I aimed to simulate the traffic without crashes. The vehicle class was modified.

In this final part of the project, I convert Vehicle class to an abstract class with move method being a pure virtual function that takes no parameters:

`virtual void move() = 0;`

In addition to the classes implemented in first and second part of the project, I created two other classes which are car and bus classes. 

#### Car:
This class should derive from the Vehicle class with the move method implementing a car movement based on the previous project rules (following waypoints, deciding on which way to go next randomly at intersections and avoiding collusions with other cars). This means the decision to select the next waypoint must be implemented in the move method.

#### Bus:
This class should derive from Vehicle class with the following additional members:

```
//Private Members:
vector<int> stops; /*is a vector of BusStop indexes that the bus will visit in order. When the bus
reaches the last stop, it should go back to the first element in the vector container and should
repeat its visits starting from the first bus stop. There should be at least 5 bus stops for a bus. Bus
stops can be common between the two busses.*/

int currentStop; //current stop index

//Public Methods:
addStop(int index);
/* Adds a BusStop index for the bus to stop at
This class should also implement the base class move method with one difference that the move method should not pick a path randomly at junctions but should take a path to reach the next bus stop. */
```

#### BusStop:
```
//Private Members:
float x; //x coordinate of the bus stop
float y; //y coordinate of the bus stop
float dir; //direction of the bus stop (determines the orientation of the bus stop on the map)

sf::Texture texture; //texture for the bus stop
sf::Sprite sprite; //sprite for the bus stop

//Public Methods:

BusStop(float x, float y, float dir);
/*Constructor for the BusStop class
parameters:
x: x coordinate of the bus stop
y: y coordinate of the bus stop
dir: bus stop direction, i.e., orientation*/

void getPosition(float &x, float &y, float &dir);
/*Returns the position and the direction of the bus stop
parameters:
x: x coordinate of the bus stop
y: y coordinate of the bus stop
dir: bus stop direction, i.e., orientation*/

void draw();
//Draws the bus stop to screen
```

### How to run the program (in Linux - Ubuntu 18.04)?

If you does not have SFML library installed on the computer, you can intall it by typing `sudo apt-get install libsfml-dev` in Terminal.

Also, you should download SFML 2.5.1 from SFML website. Put the library files that ended with '.so.2.5' to the directory that source files are in it.

Then, put SFML file (not SFML-2.5.1) that includes header files to the project directory.

You can compile the program in Terminal by typing the below command:

`g++ *.cpp *.h -o simulator.o -I. -std=c++11 -static-libgcc -L. -lsfml-window -lsfml-graphics -lsfml-system`

You should change this command if your SFML-2.5.1 file is at another directory.

Then, you can run the program as:

`./simulator.o`

### Discussion

I could write a method in Waypoint class that initiaizes waypoints randomly at every start of the window.

I took sometimes errors such as “Failed to create texture, its internal size is too high (45074856x45074472, maximum is 16384x16384)”; however, I cannot deal with this error so much.

I had problems with the implementation of traffic light group with changing the traffic light states according to the period of groups.

Creating the virtual move function to make simulatiom without accident was hard to deal with it.

I cannot change the state of the traffic lights. Cars do not stop at the traffic lights.

The buses do not stop at the bus stops.

If I run the program like 70 seconds or more, sometimes, crashes are happened.

### Screenshot of the Running Program

![Screenshot of the program](https://github.com/Demir-Utku/TrafficSimulator/blob/master/screenshot.png)
