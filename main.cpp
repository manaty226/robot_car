#include<iostream>
#include<vector>
#include"vehicle.hpp"
#include"carfactory.hpp"

int main() {
    IAbstractFactory* carfactory = new CarFactory();
    IVehicle* car = carfactory->create();

    car->enginStart();



    return 0;
}