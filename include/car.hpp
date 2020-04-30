#ifndef __CAR_GUARD__
#define __CAR_GUARD__

#include<iostream>
#include<vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include"vehicle.hpp"
#include"carmotor.hpp"
#include"engine.hpp"

class Car : public IVehicle {
public:
    Car() {};
    Car(std::vector<IMotor*> motors) {
        Car::motors = motors;
        Car::state = 0;
    };
    ~Car() {
        delete (Engine*)engine;
    };
    void forward();
    void backward(){};
    void leftForward(){};
    void rightForward(){};
    void leftBackward(){};
    void rightBackward(){};
    void setEngine(IEngine* engine);
    void enginStart();
private:
    uint8_t state;
    std::vector<IMotor*> motors;
    IEngine* engine;
};

void Car::enginStart() {
    engine->Start();
}

void Car::setEngine(IEngine* engine) {
    this->engine = engine;
}

void Car::forward() {
    motors[0]->forward(Car::state);
    motors[1]->forward(Car::state);
    motors[2]->forward(Car::state);
    motors[3]->forward(Car::state);
}



#endif