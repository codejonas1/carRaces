#pragma once
#include <iostream>
#include <thread>
#include <chrono> 
#include <unistd.h> 
#include <vector>
#include "carCords.h"
#include <mutex>
#include <condition_variable>

class Car{
  
public:
    int id;
    std::vector<carCords> &pos;
    int delay;
    float velocity;
    int &counter;

    Car(int id, int &counter, std::vector<carCords> &positions);

    int randDelay();
    float randVelocity();
    float randPosition(float end);

    void rideLaps();
    void rideInf();
};