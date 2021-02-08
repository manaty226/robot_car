#ifndef __MOTOR_GUARD__
#define __MOTOR_GUARD__

#include<iostream>

class IMotor {
public:
    virtual ~IMotor() {};
    virtual void writeShiftregistor(uint8_t state) = 0;
    virtual void motorInit() = 0;
    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual void stop() = 0;
    virtual void right() = 0;
    virtual void left() = 0;
};

#endif