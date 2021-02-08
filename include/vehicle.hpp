#ifndef __VEHICLE_GUARD__
#define __VEHICLE_GUARD__

#include"iengine.hpp"

class IVehicle {
public:
    virtual ~IVehicle() {};
    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual void right() = 0;
    virtual void left() = 0;
    virtual void leftForward() = 0;
    virtual void rightForward() = 0;
    virtual void leftBackward() = 0;
    virtual void rightBackward() = 0;
    virtual void stop() = 0;
    virtual void setEngine(IEngine* engine) = 0;
    virtual void enginStart() = 0;

};

#endif