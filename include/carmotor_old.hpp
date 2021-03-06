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
#define OUTPUT 0
void digitalWrite(uint8_t pin, uint8_t level) {
    return;
}

void delayMicroseconds(uint8_t time) {
    return;
}

int wiringPiSetup() {
    return 0;
}

void pinMode(int pin, int direction) {
    return;
}

#endif

class CarMotor : public IMotor {
public:
    CarMotor(std::string name, uint8_t fw, uint8_t bw) {
        CarMotor::name = name;
        CarMotor::fwBit = fw;
        CarMotor::bwBit = bw;
    };
    void motorInit() {};
    void forward(uint8_t &state);
    void backward(uint8_t &state);
    void stop(uint8_t &state);
    uint8_t fwBit;
    uint8_t bwBit;
private:
    std::string name;
    void writeShiftregistor(uint8_t state);
    void writeRegister(uint8_t data);
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

void CarMotor::stop(uint8_t &state) {
    state &= ~BIT(fwBit);
    state &= ~BIT(bwBit);
    CarMotor::writeShiftregistor(state);
}


void CarMotor::writeShiftregistor(uint8_t state) {

    digitalWrite(MOTORLATCH, 0);
    digitalWrite(MOTORDATA, 0);

    writeRegister(state & BIT(7));
    writeRegister(state & BIT(6));
    writeRegister(state & BIT(5));
    writeRegister(state & BIT(4));
    writeRegister(state & BIT(3));
    writeRegister(state & BIT(2));
    writeRegister(state & BIT(1));
    writeRegister(state & BIT(0));

    digitalWrite(MOTORLATCH, 1);
};

void CarMotor::writeRegister(uint8_t data)
{
    delayMicroseconds(1);
    digitalWrite (MOTORCLK, 0);
    digitalWrite(MOTORDATA, data);
    delayMicroseconds(1);
    digitalWrite(MOTORCLK, 1);
}

#endif