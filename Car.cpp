#include "Car.h"
#include "carCords.h"

Car::Car(int id, std::vector<carCords> &positions) :pos(positions)
{
    this->id = id;
    this->delay = randDelay();
    this->velocity = randVelocity();
}

int Car::randDelay(){
    return rand() % 5 + 1;
}

float Car::randVelocity(){
    // range beetwen 0.1 to 0.4
    return 0.10 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.40-0.10)));
}

float Car::randPosition(float end){
    return 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(end - 0.0)));
}

void Car::rideLaps(){
    std::this_thread::sleep_for(std::chrono::seconds(this->delay));
    int t = this->velocity * 10;
    
    for(int lap=1; lap<=3; lap++){
        for(float meter=0.0; meter < 1000.0; meter += this->velocity){
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            if(meter < 400){
                pos[this->id].x += this->velocity;
            }
            else if (meter >= 400 && meter < 500)
                pos[this->id].y += this->velocity;
            else if (meter >= 500 && meter < 900)
                pos[this->id].x -= this->velocity;
            else if (meter >= 900)
                pos[this->id].y -= this->velocity;
        }
    }
    pos[this->id].flag = true;
    return;
}

void Car::rideInf(){

    float meter = this->randPosition(1000.0);

    if (meter < 100){
        pos[this->id].x += meter;
    }else if (meter >= 100 && meter < 500){
        pos[this->id].x += 100;
        pos[this->id].y += abs(meter - 100);
    }else if (meter >= 500 && meter < 600){
        pos[this->id].x += abs(meter - 600);
        pos[this->id].y += 400;
    }else if (meter >= 600){
        pos[this->id].y += abs(meter - 1000);
    }

    this->velocity = 0.10;
    
    while(!pos[this->id].flag){
        while(meter < 1000.0){
            if(pos[this->id].flag) break;
            
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            if(meter < 100){
                pos[this->id].x += this->velocity;
                meter += this->velocity;
            }
            else if (meter >= 100 && meter < 500){
                if(pos.size() >= 3){
                    int counter = 0;
                    for(int i=3; i<pos.size(); i++) if(pos[i].y > 150) counter++;
                
                    if(counter != 0 && (pos[this->id].y >16 && pos[this->id].y < 18)){
                        pos[this->id].y += 0;
                        meter += 0;
                    }else{
                        pos[this->id].y += this->velocity;
                        meter += this->velocity;
                    }
                }
            }
            else if (meter >= 500 && meter < 600){
                pos[this->id].x -= this->velocity;
                meter += this->velocity;
            }
            else if (meter >= 600){
                pos[this->id].y -= this->velocity;
                meter += this->velocity;
            }
                
        }
        meter = 0.0;
        pos[this->id].x = 80;
        pos[this->id].y = -100;
    }
    return;
}