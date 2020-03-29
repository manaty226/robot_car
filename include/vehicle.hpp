#ifndef __VEHICLE_GUARD__
#define __VEHICLE_GUARD__

class IVehicle {
public:
    virtual ~IVehicle() {};
    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual void leftForward() = 0;
    virtual void rightForward() = 0;
    virtual void leftBackward() = 0;
    virtual void rightBackward() = 0;
};

#endif