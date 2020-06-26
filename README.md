## TrafficSimulator

### Project Objective

The objective of this project is to implement a traffic simulator using object oriented programming methods. The simulator simulates an urban environment with various vehicles moving in traffic.

The project was implemented using SFML Graphics and Multimedia library. I used some sprite objects which are road pieces, vehicles, way points, traffic lights, and bus stops objects.

### First Part of the Project

In the first phase of the project, I am expected to draw the environment and move a single car around the track.

Simulation has way points that show the points in the track that the car will follow and the direction the car may go.

Every road tile is a 239 by 239 pixel graphic sprite. Each tile has a set of two or more way points on it. Each way point has an internal index starting from 0 within the tile it belongs to as well as internal x-/y- coordinates relative to the top-left corner of the tile. The figure below is just an example of road tiles with way points on it and shows a tile and the way points belonging to it along with the internal way point indexes and their relative coordinates with respect to the top-left corner of the tile.

![Roadtile with waypoints on it](https://imgur.com/xrdCpYJ)
