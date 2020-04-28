#ifndef __CAR_GUARD__
#define __CAR_GUARD__

#include<iostream>
#include<vector>
#include"vehicle.hpp"
#include"carmotor.hpp"

class Car : public IVehicle {
public:
    Car() {};
    Car(std::vector<IMotor*> motors) {
        Car::motors = motors;
        Car::state = 0;
        std::cout << "state is " << state << std::endl;
    };
    ~Car() {};
    void forward();
    void backward(){};
    void leftForward(){};
    void rightForward(){};
    void leftBackward(){};
    void rightBackward(){};
private:
    uint8_t state;
    std::vector<IMotor*> motors;
};

void Car::forward() {
    std::cout << "go forward." << std::endl;
    motors[0]->forward(Car::state);
    std::cout << Car::state << std::endl;
    motors[1]->forward(Car::state);
    motors[2]->forward(Car::state);
    motors[3]->forward(Car::state);
}

#endif