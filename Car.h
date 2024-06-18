#pragma once
#include <iostream>
#include <thread>
#include <chrono> 
#include <unistd.h> 
#include <vector>
#include "carCords.h"
#include <mutex> 

class Car{
  
public:
    int id;
    std::vector<carCords> &pos;
    int delay;
    float velocity;

    Car(int id, std::vector<carCords> &positions);

    int randDelay();
    float randVelocity();
    float randPosition(float end);

    void rideLaps();
    void rideInf();
};