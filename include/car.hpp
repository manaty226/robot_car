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
    Car(IMotor* motor) {
        Car::motor = motor;
        Car::state = 0;
    };
    ~Car() {
        delete (Engine*)engine;
        delete (IMotor*)motor;
    };
    void forward();
    void backward();
    void right();
    void left();
    void leftForward();
    void rightForward();
    void leftBackward();
    void rightBackward();
    void stop();
    void setEngine(IEngine* engine);
    void enginStart();
private:
    uint8_t state;
    IMotor* motor;
    IEngine* engine;
};

void Car::enginStart() {
    engine->Start();
}

void Car::setEngine(IEngine* engine) {
    this->engine = engine;
}

void Car::forward() {
    motor->forward();
}

void Car::backward() {
    motor->backward();
}

void Car::right()
{
    motor->right();
}

void Car::left()
{
    motor->left();
}


void Car::rightForward() {
    // motors[0]->forward(Car::state);
    // motors[1]->stop(Car::state);
    // motors[2]->forward(Car::state);
    // motors[3]->stop(Car::state);
}

void Car::leftForward() {
    // motors[0]->stop(Car::state);
    // motors[1]->forward(Car::state);
    // motors[2]->stop(Car::state);
    // motors[3]->forward(Car::state);
}

void Car::rightBackward() {
}

void Car::leftBackward() {
}

void Car::stop() {
    motor->stop();
}



#endif