#include <iostream>
#include <ncurses.h>
#include <vector>
#include <queue>
#include "Car.cpp"

bool stillGenerate = true;
bool stillShow = true;
std::vector<carCords> positions;
std::vector<std::thread> ThreadVector;

void isSpace(){
    char k;
    k = getch();

    if(k == ' ') {
        stillGenerate = false;
        positions[0].flag  = true;
        positions[1].flag  = true;
        positions[2].flag  = true;
        return;
    } 
}

void drawInfRoad(){
    int startX = 53;
    int endX = 80;

    int startY = 2;
    int endY = 31;

    for(int j=startX; j<endX; j++){
        move(startY, j);
        printw("-");
        
        move(endY, j);
        printw("-");
    }

    for(int j=startY; j<endY; j++){
        move(j, startX);
        printw("|");

        move(j, endX);
        printw("|");
    }

    for(int j=startY+4; j<endY-4; j++){
        move(j, startX+7);
        printw("|");

        move(j, endX-7);
        printw("|");
    }

    for(int j=startX; j<endX; j++){
        move(startY, j);
        printw("-");
        
        move(endY, j);
        printw("-");
    }

    for(int j=startX+7; j<endX-7; j++){
        move(startY+4, j);
        printw("-");
        
        move(endY-4, j);
        printw("-");
    }
}

void drawLapsRoad(){
    int startX = 22;
    int endX = 112;

    int startY = 12;
    int endY = 22;

    for(int j=startX; j<endX; j++){
        move(startY, j);
        printw("-");
        
        move(endY, j);
        printw("-");
    }

    for(int j=startX+10; j<endX-10; j++){
        move(startY+3, j);
        printw("-");
        
        move(endY-3, j);
        printw("-");
    }

    for(int j=startY+3; j<endY-3; j++){
        move(j, startX+10);
        printw("|");

        move(j, endX-10);
        printw("|");
    }

    for(int j=startY; j<endY; j++){
        move(j, startX);
        printw("|");

        move(j, endX);
        printw("|");
    }
}

void showPosition(){
    while(stillShow){
        erase();
        drawInfRoad();
        drawLapsRoad();

        for(int id=0; id<positions.size(); id++){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

            if(positions[id].flag) continue;
            
            int x = positions[id].x / 5;
            int y = positions[id].y / 15;

            move(y + 10, x + 40);

            std::string str = "|" + std::to_string(id) + "|";
            char const *carId = str.c_str();
            printw("%s", carId);
        }
        refresh();
    }
}  

void carRaces(){
    initscr();
    noecho();
    curs_set(0);

    std::thread updateConsole(showPosition);
    std::thread catchSpace(isSpace);

    carCords cc;
    cc.x = 80;
    cc.y = -100;

    positions.push_back(cc);
    positions.push_back(cc);
    positions.push_back(cc);

    int id=0;

    Car firstCar = Car(id++, positions);
    Car secondCar = Car(id++, positions);
    Car thirdCar = Car(id++, positions);

    ThreadVector.push_back(std::thread(&Car::rideInf, firstCar));
    ThreadVector.push_back(std::thread(&Car::rideInf, secondCar));
    ThreadVector.push_back(std::thread(&Car::rideInf, thirdCar));

    while(stillGenerate){
        cc.x = -70;
        cc.y = 60;
        positions.push_back(cc);

        Car car = Car(id, positions);
    
        ThreadVector.push_back(std::thread(&Car::rideLaps, car));    
        std::this_thread::sleep_for(std::chrono::seconds(5));
        id++;
    }

    for(auto& t: ThreadVector) t.join();

    catchSpace.join();

    stillShow = false;
    updateConsole.join();

    endwin();
}

int main(){
    srand(time(NULL));

    carRaces();

    return 0;
}

