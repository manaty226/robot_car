#ifndef __IENGINE_GUARD__
#define __IENGINE_GUARD__


class IEngine {
public:
    virtual ~IEngine() {};
    virtual void Start()=0;
    // virtual void Stop();
};

#endif