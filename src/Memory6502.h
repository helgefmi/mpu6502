#ifndef __Memory6502_H
#define __Memory6502_H

#include "Memory.h"
#include "Mpu6502.h"
#include <iostream>

class Memory6502 : public Memory
{
    public:
        Memory6502(Mpu6502 *mpu) : mpu(mpu), Memory(0x10000) { }

        inline const uint8_t get_immediate() const;
        inline const uint8_t get_zero_page() const;
        inline const uint8_t get_zero_page_x() const;
        inline const uint8_t get_zero_page_y() const;
        inline const uint16_t get_absolute() const;
        inline const uint16_t get_absolute_x() const;
        inline const uint16_t get_absolute_y() const;
        inline const uint16_t get_indirect_x() const;
        inline const uint16_t get_indirect_y() const;
    private:
        Mpu6502 *mpu;
};

inline const uint8_t Memory6502::get_immediate() const // {{{
{
    return byteAt(mpu->reg.pc);
} // }}}
inline const uint8_t Memory6502::get_zero_page() const // {{{
{
    return byteAt(mpu->reg.pc);
} // }}}
inline const uint8_t Memory6502::get_zero_page_x() const // {{{
{
    return mpu->reg.x + byteAt(mpu->reg.pc);
} // }}}
inline const uint8_t Memory6502::get_zero_page_y() const // {{{
{
    return mpu->reg.y + byteAt(mpu->reg.pc);
} // }}}
inline const uint16_t Memory6502::get_absolute() const // {{{
{
    return wordAt(mpu->reg.pc);
} // }}}
inline const uint16_t Memory6502::get_absolute_x() const // {{{
{
    uint16_t arg = wordAt(mpu->reg.pc);
    uint16_t arg_and_x = arg + mpu->reg.x;

    if (arg_and_x & 0xFF00 != arg & 0xFF00)
        mpu->extra_cycles += 1;

    return arg_and_x;
} // }}}
inline const uint16_t Memory6502::get_absolute_y() const // {{{
{
    uint16_t arg = wordAt(mpu->reg.pc);
    uint16_t arg_and_y = arg + mpu->reg.y;

    if (arg_and_y & 0xFF00 != arg & 0xFF00)
        mpu->extra_cycles += 1;

    return arg_and_y;
} // }}}
inline const uint16_t Memory6502::get_indirect_x() const // {{{
{
    return wordAt(get_zero_page_x());
} // }}}
inline const uint16_t Memory6502::get_indirect_y() const // {{{
{
    uint16_t arg = wordAt(byteAt(mpu->reg.pc));
    uint16_t arg_and_y = arg + mpu->reg.y;

    if (arg_and_y & 0xFF00 != arg & 0xFF00)
        mpu->extra_cycles += 1;

    return arg_and_y;
} // }}}

#endif
