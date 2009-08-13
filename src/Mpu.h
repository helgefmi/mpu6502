#ifndef __Mpu_H
#define __Mpu_H

#include <string>

class Mpu
{
    public:
        virtual void reset() = 0;
        virtual void step() = 0;
        virtual void loop() = 0;
        virtual void load_binary_file(const std::string&) = 0;
};

#endif
