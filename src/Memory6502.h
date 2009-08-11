#ifndef __Memory6502_H
#define __Memory6502_H

#include "Memory.h"
#include "Mpu6502.h"
#include <iostream>

class Memory6502 : public Memory
{
    public:
        Memory6502(Mpu6502 *mpu) : mpu(mpu), Memory(0x10000) { }

        inline uint8_t get_immediate();
        inline uint8_t get_zero_page();
        inline uint8_t get_zero_page_x();
        inline uint8_t get_zero_page_y();
        inline uint16_t get_absolute();
        inline uint16_t get_absolute_x();
        inline uint16_t get_absolute_y();
        inline uint16_t get_indirect_x();
        inline uint16_t get_indirect_y();
    private:
        Mpu6502 *mpu;
};

inline uint8_t Memory6502::get_immediate() // {{{
{
    return byteAt(mpu->reg.pc);
} // }}}
inline uint8_t Memory6502::get_zero_page() // {{{
{
    return byteAt(mpu->reg.pc);
} // }}}
inline uint8_t Memory6502::get_zero_page_x() // {{{
{
    return mpu->reg.x + byteAt(mpu->reg.pc);
} // }}}
inline uint8_t Memory6502::get_zero_page_y() // {{{
{
    return mpu->reg.y + byteAt(mpu->reg.pc);
} // }}}
inline uint16_t Memory6502::get_absolute() // {{{
{
    return wordAt(mpu->reg.pc);
} // }}}
inline uint16_t Memory6502::get_absolute_x() // {{{
{
    uint16_t arg = wordAt(mpu->reg.pc);
    uint16_t arg_and_x = arg + mpu->reg.x;

    if (arg_and_x & 0xFF00 != arg & 0xFF00)
        mpu->extra_cycles += 1;

    return arg_and_x;
} // }}}
inline uint16_t Memory6502::get_absolute_y() // {{{
{
    uint16_t arg = wordAt(mpu->reg.pc);
    uint16_t arg_and_y = arg + mpu->reg.y;

    if (arg_and_y & 0xFF00 != arg & 0xFF00)
        mpu->extra_cycles += 1;

    return arg_and_y;
} // }}}
inline uint16_t Memory6502::get_indirect_x() // {{{
{
    return wordAt(get_zero_page_x());
} // }}}
inline uint16_t Memory6502::get_indirect_y() // {{{
{
    uint16_t arg = wordAt(byteAt(mpu->reg.pc));
    uint16_t arg_and_y = arg + mpu->reg.y;

    if (arg_and_y & 0xFF00 != arg & 0xFF00)
        mpu->extra_cycles += 1;

    return arg_and_y;
} // }}}

#endif
