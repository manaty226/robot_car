#ifndef __CARFACTORY_GUARD__
#define __CARFACTORY_GUARD__

#include<vector>
#include"ifactory.hpp"
#include"car.hpp"
#include"carmotor.hpp"
#include"engine.hpp"

class CarFactory : public IAbstractFactory {

public:
    CarFactory() {};
    ~CarFactory() {};
    IVehicle* create();
};

IVehicle* CarFactory::create() {
    std::vector<IMotor*> motors;
    IMotor* motor_1 = new CarMotor("left front", 3, 2);
    motors.push_back(motor_1);

    IMotor* motor_2 = new CarMotor("right front", 4, 1);
    motors.push_back(motor_2);

    IMotor* motor_3 = new CarMotor("left back", 5, 7);
    motors.push_back(motor_3);

    IMotor* motor_4 = new CarMotor("right back", 0, 6);
    motors.push_back(motor_4);

    // エンジンのセット
    IEngine* engine = new Engine();
    IVehicle* car = new Car(motors);
    car->setEngine((IEngine*)engine);

    return car;
}

#endif