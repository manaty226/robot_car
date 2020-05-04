#ifndef __MOTOR_GUARD__
#define __MOTOR_GUARD__

#include<iostream>

class IMotor {
public:
    virtual ~IMotor() {};
    virtual void writeShiftregistor(uint8_t state) = 0;
    virtual void motorInit() = 0;
    virtual void forward(uint8_t &state) = 0;
    virtual void backward(uint8_t &state) = 0;
    virtual void stop(uint8_t &state) = 0;
};

#endif