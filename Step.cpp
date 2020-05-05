#include "Step.h"

Step::Step ()
{
    setSleep(false);
}

Step::Step (byte cv, int value)
{
    setCV(cv, value);
    setSleep(false);
}

void Step::setCV(byte cv, int value)
{
    _cv[cv] = value;
}

int Step::getCV(byte cv)
{
    if (getSleep()) {
        return 0;
    }

    return _cv[cv];
}

void Step::setSleep(boolean sleep)
{
    _sleep = sleep;
}

boolean Step::getSleep()
{
    return _sleep;
}