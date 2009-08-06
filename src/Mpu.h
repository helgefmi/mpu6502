#ifndef __Mpu_H
#define __Mpu_H

#include "Memory.h"
#include <stdint.h>

class Mpu
{
    public:
        virtual void reset() = 0;
        virtual int tick() = 0;
        virtual void loop() = 0;
};

#endif
