#ifndef __Mpu_H
#define __Mpu_H

#include "Memory.h"
#include <string>
#include <stdint.h>

class Mpu
{
    public:
        virtual void reset() = 0;
        virtual int tick() = 0;
        virtual void loop() = 0;
        virtual void load_binary_file(std::string) = 0;
};

#endif
