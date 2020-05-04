#include<iostream>
#include<vector>
#include"vehicle.hpp"
#include"carfactory.hpp"

int main() {
    IAbstractFactory* carfactory = new CarFactory();
    IVehicle* car = carfactory->create();

    car->enginStart();
    int i = 10000;

    while(i--) {
        car->forward();
    }
    car->stop();

    delete car;

    return 0;
}