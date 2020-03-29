#ifndef __IABSTRACTFACTORY_GUARD__
#define __IABSTRACTFACTORY_GUARD__

#include"vehicle.hpp"

class IAbstractFactory {
public:
    virtual ~IAbstractFactory() {};
    virtual IVehicle* create() = 0;
};

#endif