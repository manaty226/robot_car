#ifndef __CARMOTOR_GUARD__
#define __CARMOTOR_GUARD__

#include<iostream>
#include<string>
#include"motor.hpp"
#ifndef WOWIRINGPI
#include<wiringPi.h>
#endif

#define MOTORDATA   27
#define MOTORCLK    28
#define MOTORLATCH  29
#define BIT(bit) (1 << (bit))

#ifdef WOWIRINGPI
void digitalWrite(uint8_t pin, uint8_t level) {
    return;
}

void delayMicroseconds(uint8_t time) {
    return;
}

void wiringPiSetup(uint8_t time) {
    return;
}

void pinMode(int pin, )

#endif

class CarMotor : public IMotor {
public:
    CarMotor(std::string name, uint8_t fw, uint8_t bw) {
        CarMotor::name = name;
        CarMotor::fwBit = fw;
        CarMotor::bwBit = bw;

        int res = wiringPiSetup();
        cout << res << endl;
        pinMode(29, OUTPUT);
        pinMode(27, OUTPUT);
        pinMode(28, OUTPUT); 

    };
    void motorInit() {};
    void forward(uint8_t &state);
    void backward(uint8_t &state);
    uint8_t fwBit;
    uint8_t bwBit;
private:
    std::string name;
    void writeShiftregistor(uint8_t state);
};

void CarMotor::forward(uint8_t &state) {
    state |= BIT(fwBit);
    state &= ~BIT(bwBit);
    CarMotor::writeShiftregistor(state);
}

void CarMotor::backward(uint8_t &state) {
    state &= ~BIT(fwBit);
    state |= BIT(bwBit);
    CarMotor::writeShiftregistor(state);
}

void CarMotor::writeShiftregistor(uint8_t state) {
    std::cout << "write to shift registor" << " " << CarMotor::name << std::endl;

    digitalWrite(MOTORLATCH, 0);
    digitalWrite(MOTORDATA, 0);

    for(int i = 0; i < 8; i++) {
        delayMicroseconds(1);
        if(state & BIT(7 - i)) {
            digitalWrite(MOTORDATA, 1);
        } else {
            digitalWrite(MOTORDATA, 0);
        }
        delayMicroseconds(1);
        digitalWrite(MOTORCLK, 1);
    }

    digitalWrite(MOTORLATCH, 1);
};

#endif