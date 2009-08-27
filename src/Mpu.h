#ifndef __Mpu_H
#define __Mpu_H

#include <stdint.h>
#include <string>

class Mpu
{
    public:
        virtual void reset() = 0;
        virtual void step() = 0;
        virtual void run() = 0;
        virtual void load_binary_file(const std::string&, uint16_t) = 0;
};

#endif
