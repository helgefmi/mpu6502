#ifndef __6502_H
#define __6502_H

#include "Mpu.h"
#include "defines.h"
#include <string>
#include <stdint.h>
#include <bitset>

typedef struct registers
{
    uint16_t        pc;    /* Program Counter */
    uint8_t         sp;    /* Stack Pointer */
    uint8_t         ac;    /* Accumulator */
    uint8_t         x, y;  /* General registers */
    std::bitset<8>  ps;    /* Processor Status */
} registers_t;

class Memory6502;

class Mpu6502 : public Mpu
{
    friend class Memory6502;
    friend class TestSuite;

    public:
        Mpu6502();
        ~Mpu6502();

#if 0
        static const int op_cycles[];
#endif

        void reset();
        void step();
        void loop();
        void load_binary_file(const std::string&);

        std::string to_string() const;

    private:
        registers_t reg;

        Memory6502 *mem;

        inline void set_nz_flags(const uint8_t);
};

/* Inlines */
inline void Mpu6502::set_nz_flags(const uint8_t value) // {{{
{
    reg.ps[FLAG_ZERO] = (0 == value);
    reg.ps[FLAG_NEGATIVE] = ((int8_t) value) < 0;
} // }}}

#endif
