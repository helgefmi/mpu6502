#ifndef __Memory6502_H
#define __Memory6502_H

#include "Memory.h"
#include "Mpu6502.h"

class Memory6502 : public Memory
{
    public:
        Memory6502(Mpu6502 *mpu) : mpu(mpu)
        {
            setSize(0x10000);
            memory = new uint8_t[size];
            reset();
        }

        inline int8_t get_immediate();
        inline int8_t get_zero_page();
        inline int8_t get_zero_page_x();
        inline int8_t get_zero_page_y();
        inline int16_t get_absolute();
        inline int16_t get_absolute_x();
        inline int16_t get_absolute_y();
        inline int16_t get_indirect_x();
        inline int16_t get_indirect_y();
    private:
        Mpu6502 *mpu;
};

inline int8_t Memory6502::get_immediate() // {{{
{
    return byteAt(mpu->reg.pc);
} // }}}
inline int8_t Memory6502::get_zero_page() // {{{
{
    return byteAt(mpu->reg.pc);
} // }}}
inline int8_t Memory6502::get_zero_page_x() // {{{
{
    return mpu->reg.x + byteAt(mpu->reg.pc);
} // }}}
inline int8_t Memory6502::get_zero_page_y() // {{{
{
    return mpu->reg.y + byteAt(mpu->reg.pc);
} // }}}
inline int16_t Memory6502::get_absolute() // {{{
{
    return wordAt(mpu->reg.pc);
} // }}}
inline int16_t Memory6502::get_absolute_x() // {{{
{
    int16_t from_mem = wordAt(mpu->reg.pc);
    int16_t ret = from_mem + mpu->reg.x;

    if (ret & 0xFF00 != from_mem & 0xFF00)
        mpu->extra_cycles += 1;

    return ret;
} // }}}
inline int16_t Memory6502::get_absolute_y() // {{{
{
    int16_t from_mem = wordAt(mpu->reg.pc);
    int16_t ret = from_mem + mpu->reg.y;

    if (ret & 0xFF00 != from_mem & 0xFF00)
        mpu->extra_cycles += 1;

    return ret;
} // }}}
inline int16_t Memory6502::get_indirect_x() // {{{
{
    return wordAt(get_zero_page_x());
} // }}}
inline int16_t Memory6502::get_indirect_y() // {{{
{
    return 0;
} // }}}

#endif
