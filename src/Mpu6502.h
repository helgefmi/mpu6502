#ifndef __6502_H
#define __6502_H

#include "Mpu.h"
#include <string>
#include <stdint.h>

class Memory6502;
class TestSuite;
typedef struct registers
{
    uint16_t    pc;    /* Processor Status */
    int8_t      ac;    /* Accumulator */
    int8_t      x, y;  /* General registers */
    uint8_t     sp;    /* Stack Pointer */
} registers_t;

class Mpu6502 : public Mpu
{
    friend class Memory6502;
    friend class TestSuite;
    public:
        Mpu6502();
        ~Mpu6502();

        static int op_cycles[];

        void reset();
        int step();
        void loop();
        void load_binary_file(const std::string&);

        std::string to_string();

    private:
        registers_t reg;

        int extra_cycles;
        Memory6502 *mem;

        inline void set_nz_flags(const int8_t);
};

#endif
