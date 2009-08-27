#ifndef __UTIL_H
#define __UTIL_H

#include <stdint.h>

class Util
{
    public:
        static uint8_t bin2bcd(const uint8_t);
        static uint8_t bcd2bin(const uint8_t);
};

#endif
