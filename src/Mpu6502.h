#ifndef __6502_H
#define __6502_H

#include <stdint.h>
#include <string>
#include <bitset>
#include "Mpu.h"
#include "Memory.h"
#include "defines.h"

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
        void run();
        void load_binary_file(const std::string&, uint16_t);

        void subscribe_to_write(uint16_t, uint16_t, write_callback_t);
        void subscribe_to_read(uint16_t, uint16_t, read_callback_t);

        std::string to_string() const;

    private:
        registers_t reg;

        Memory6502 *mem_ptr;

        inline void set_nz_flags(const uint8_t);
        inline void push_to_stack(const uint8_t);
        inline uint8_t pull_from_stack();
};

/* Inlines */
#include "Memory6502.h"
inline void Mpu6502::set_nz_flags(const uint8_t value) // {{{
{
    reg.ps[FLAG_ZERO] = (0 == value);
    reg.ps[FLAG_NEGATIVE] = ((int8_t) value) < 0;
} // }}}
inline void Mpu6502::push_to_stack(const uint8_t value) // {{{
{
    mem_ptr->set_byte(0x100 + reg.sp, value);
    --reg.sp;
} // }}}
inline uint8_t Mpu6502::pull_from_stack() // {{{
{
    ++reg.sp;
    uint8_t ret = mem_ptr->get_byte(0x100 + reg.sp);

    return ret;
} // }}}

inline void Mpu6502::subscribe_to_write(uint16_t from_offset, uint16_t to_offset, write_callback_t fp) // {{{
{
    mem_ptr->subscribe_to_write(from_offset, to_offset, fp);
} // }}}
inline void Mpu6502::subscribe_to_read(uint16_t from_offset, uint16_t to_offset, read_callback_t fp) // {{{
{
    mem_ptr->subscribe_to_read(from_offset, to_offset, fp);
} // }}}
#endif
