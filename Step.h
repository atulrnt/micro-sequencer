#include "Arduino.h"

class Step
{
    public:
        Step();
        Step(byte, int);

        void setCV(byte, int);
        int getCV(byte);
        void setSleep(boolean);
        boolean getSleep();

    private:
        int _cv[2];
        boolean _sleep;
};