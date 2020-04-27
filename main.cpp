#include<iostream>
#include<vector>
#include"car.hpp"
#include"carmotor.hpp"
#include"carfactory.hpp"

#define __cplusplus

int main() {
    IAbstractFactory* carfactory = new CarFactory();
    IVehicle* car = carfactory->create();

    car->forward();


    return 0;
}