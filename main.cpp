#include<iostream>
#include<vector>
#include <ncurses.h>
#include<wiringPi.h>
#include"vehicle.hpp"
#include"carfactory.hpp"

int main() {

    IAbstractFactory* carfactory = new CarFactory();
    IVehicle* car = carfactory->create();

    car->enginStart();
    car->stop();
    int i = 1;
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    int prev = 'e';
    while(true) {
        int c = getch();
        if(c == 'e') break;
        switch(c) 
        {
            case KEY_UP:
                car->forward();
                break;
            case KEY_DOWN:
                car->backward();
                break;
            case KEY_LEFT:
                car->left();
                break;
            case KEY_RIGHT:
                car->right();
                break;
            default:
                car->stop();
                break;
        }
        usleep(70000);
        prev = c;
    }
    endwin();
    car->stop();
    return 0;
}