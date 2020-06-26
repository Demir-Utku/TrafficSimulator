#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "trafficlight.h"

using namespace std;
using namespace std::chrono;

#ifndef TRAFFICLIGHTGROUP_H
#define TRAFFICLIGHTGROUP_H

class TrafficLightGroup
{
    TrafficLight* head; //Pointer to the head of the traffic light in the group
    TrafficLight* greenLight; //Traffic light when the state is green

    float duration; //Period
public:
    float time; //Current time elapsed in seconds

    //Constructor for TrafficLightGroup class
    // duration: TrafficLight period
    TrafficLightGroup(float duration): head(NULL), greenLight(NULL), time(0){
        //Initialize head, tail, and greenLight pointers to NULL and time to 0.
        this->duration = duration; //Initialize the duration.
    }

    //Adds traffic lights to traffic light groups
    //light: Pointer to the traffic light object to be added to the group
    void add(TrafficLight* light) {
        light->setNext(NULL);
        TrafficLight *tmp = head;

        if(tmp != NULL) {
            while(tmp->returnNext() != NULL)
                tmp = tmp->returnNext();
            tmp->setNext(light);
        }

        else {
            head = light;
        }
    }

    /* If the traffic light group timer reaches the switching period (i.e., duration member variable) of
    the group, the next light in the group is turned into green while the others are turned into red
    */
    //timestep in seconds
    void simulate(float timestep) {
            this->duration = timestep;
            this->time = timestep * 6;

            //TrafficLightGroups according to roadtile types
            TrafficLightGroup group1(timestep); //TTOP
            TrafficLightGroup group2(timestep); //TRIGHT
            TrafficLightGroup group3(timestep); //CROSS

            //Create traffic lights and set their states.
            TrafficLight* light1 = new TrafficLight(2*239 + 70, 250, 180, GREEN);
            light1->setState(GREEN);
            TrafficLight* light2 = new TrafficLight(2*239 + 240, 170, 90, RED);
            light2->setState(RED);
            TrafficLight* light3 = new TrafficLight(4*239 + 70, 2*239 + 70, 180, RED);
            light3->setState(RED);
            TrafficLight* light4 = new TrafficLight(4*239 + 50, 2*239 + 170, 0, GREEN);
            light4->setState(GREEN);
            TrafficLight* light5 = new TrafficLight(2*239 + 40, 2*239 + 170, 90, GREEN);
            light5->setState(GREEN);
            TrafficLight* light6 = new TrafficLight(2*239 + 70, 2*239 + 70, 180, RED);
            light6->setState(RED);
            TrafficLight* light7 = new TrafficLight(2*239 + 200, 2*239 + 70, 270, RED);
            light7->setState(RED);

            //Adds t lights to the groups
            group1.add(light1);
            group1.add(light2);
            group2.add(light3);
            group2.add(light4);
            group3.add(light5);
            group3.add(light6);
            group3.add(light7);

            float i = 0;
            while(i <= time) {
                //The states of t lights changed in some exact times
                //These are 5 * timestep, 4 * timestep, etc..
                if(i == time - 5 * timestep) {
                    light1->setState(RED);
                    light2->setState(GREEN);
                    light3->setState(GREEN);    //Changing their states
                    light4->setState(RED);
                    light5->setState(RED);
                    light6->setState(GREEN);
                    light7->setState(RED);
                }

                else if(i == time - 4 * timestep) {
                    light1->setState(GREEN);
                    light2->setState(RED);
                    light3->setState(RED);
                    light4->setState(GREEN);
                    light5->setState(RED);
                    light6->setState(RED);
                    light7->setState(GREEN);
                }

                else if(i == time - 3 * timestep) {
                    light1->setState(RED);
                    light2->setState(GREEN);
                    light3->setState(RED);
                    light4->setState(GREEN);
                    light5->setState(GREEN);
                    light6->setState(RED);
                    light7->setState(RED);
                }

                else if(i == time - 2 * timestep) {
                    light1->setState(GREEN);
                    light2->setState(RED);
                    light3->setState(GREEN);
                    light4->setState(RED);
                    light5->setState(RED);
                    light6->setState(GREEN);
                    light7->setState(RED);
                }

                else if(i == time - timestep) {
                    light1->setState(RED);
                    light2->setState(GREEN);
                    light3->setState(RED);
                    light4->setState(GREEN);
                    light5->setState(RED);
                    light6->setState(RED);
                    light7->setState(GREEN);
                }

                else if(i == time) {
                    light1->setState(GREEN);
                    light2->setState(RED);
                    light3->setState(RED);
                    light4->setState(GREEN);
                    light5->setState(GREEN);
                    light6->setState(RED);
                    light7->setState(RED);
                }

                i += 1; //Increase i after operations
            }
        }
};

#endif // TRAFFICLIGHTGROUP_H
