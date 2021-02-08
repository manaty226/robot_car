#ifndef __CARMOTOR_GUARD__
#define __CARMOTOR_GUARD__

#include<iostream>
#include<string>
#include<map>
#include"motor.hpp"
#include<wiringPi.h>

#define MOTORDATA   27
#define MOTORCLK    28
#define MOTORLATCH  29
#define BIT(bit) (1 << (bit))

enum class Direction {
    FORWARD,
    BACKWARD,
    RIGHTFORWARD,
    LEFTFORWARD,
    STOP,
    RIGHT,
    LEFT
};

class CarMotor : public IMotor {
public:
    void motorInit() {};
    void forward();
    void backward();
    void stop();
    void right();
    void left();
private:
    void writeShiftregistor(uint8_t state);
    void writeRegister(uint8_t data);
    void mySoftPwmController(int idx, int speed);
    void get_pwm_timestamp();
    int prev_time[4];
    int curr_time[4];
    unsigned char flag[4];
    int time_stamp[4];
    unsigned int motor_pwm[4];
    std::map<Direction,int> directions = {
        {Direction::FORWARD,   57},
        {Direction::BACKWARD, 198},
        {Direction::STOP,       0},
        {Direction::RIGHT,    106},
        {Direction::LEFT,     149},
    };
};

void CarMotor::forward()
{
    CarMotor::writeShiftregistor(directions[Direction::FORWARD]);
}

void CarMotor::backward()
{
    CarMotor::writeShiftregistor(CarMotor::directions[Direction::BACKWARD]);
}

void CarMotor::stop()
{
    CarMotor::writeShiftregistor(CarMotor::directions[Direction::STOP]);
}

void CarMotor::right()
{
    CarMotor::writeShiftregistor(CarMotor::directions[Direction::RIGHT]);
}

void CarMotor::left()
{
    CarMotor::writeShiftregistor(CarMotor::directions[Direction::LEFT]);
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

// void CarMotor::mySoftPwmController(int idx, int speed) 
// {

//   int* prev_time_ptr = &prev_time[idx];
//   int* curr_time_ptr = &curr_time[idx];
//   int* time_stamp_ptr = &time_stamp[idx];
//   unsigned char* flag_ptr = &flag[idx];

//   if(!(*flag_ptr)) {
//       *flag_ptr = 1;
//       *prev_time_ptr = get_pwm_timestamp();
//   }
//   *curr_time_ptr = get_pwm_timestamp();
//   *time_stamp_ptr = *curr_time_ptr - *prev_time_ptr;

//   if(*time_stamp_ptr > 0 && (unsigned int)*time_stamp_ptr <= 2 * halfPWMPeriod) {
//     if(*time_stamp_ptr <= speed) GPIO_SET = 1 << motor_pwm[idx];
//     else GPIO_CLR = 1 << motor_pwm[idx];
//   }
//   if((unsigned int)*time_stamp_ptr > 2 * halfPWMPeriod) *flag_ptr = 0;

// }

// uint64_t CarMotor::get_pwm_timestamp()
// {
//   struct timespec t;
//   if (clock_gettime(CLOCK_MONOTONIC_RAW, &t) != 0) {
//     return 0;
//   }
//   return (uint64_t) t.tv_sec * 1000000 + t.tv_nsec / 1000;
// }


#endif