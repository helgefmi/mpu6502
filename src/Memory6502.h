#ifndef __Memory6502_H
#define __Memory6502_H

#include "Memory.h"
#include "Mpu6502.h"

class Memory6502 : public Memory
{
    public:
        Memory6502(Mpu6502 *mpu_ptr) : Memory(0x10000), mpu_ptr(mpu_ptr) { }

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
        Mpu6502 *mpu_ptr;
};

inline uint8_t Memory6502::get_immediate() // {{{
{
    return get_byte(mpu_ptr->reg.pc);
} // }}}
inline uint8_t Memory6502::get_zero_page() // {{{
{
    return get_byte(mpu_ptr->reg.pc);
} // }}}
inline uint8_t Memory6502::get_zero_page_x() // {{{
{
    return mpu_ptr->reg.x + get_byte(mpu_ptr->reg.pc);
} // }}}
inline uint8_t Memory6502::get_zero_page_y() // {{{
{
    return mpu_ptr->reg.y + get_byte(mpu_ptr->reg.pc);
} // }}}
inline uint16_t Memory6502::get_absolute() // {{{
{
    return get_word(mpu_ptr->reg.pc);
} // }}}
inline uint16_t Memory6502::get_absolute_x() // {{{
{
    uint16_t arg = get_word(mpu_ptr->reg.pc);
    uint16_t arg_and_x = arg + mpu_ptr->reg.x;

#if 0
    if (arg_and_x & 0xFF00 != arg & 0xFF00)
        mpu_ptr->extra_cycles += 1;
#endif

    return arg_and_x;
} // }}}
inline uint16_t Memory6502::get_absolute_y() // {{{
{
    uint16_t arg = get_word(mpu_ptr->reg.pc);
    uint16_t arg_and_y = arg + mpu_ptr->reg.y;

#if 0
    if (arg_and_y & 0xFF00 != arg & 0xFF00)
        mpu_ptr->extra_cycles += 1;
#endif

    return arg_and_y;
} // }}}
inline uint16_t Memory6502::get_indirect_x() // {{{
{
    return get_word(get_zero_page_x());
} // }}}
inline uint16_t Memory6502::get_indirect_y() // {{{
{
    uint16_t arg = get_word(get_byte(mpu_ptr->reg.pc));
    uint16_t arg_and_y = arg + mpu_ptr->reg.y;

#if 0
    if (arg_and_y & 0xFF00 != arg & 0xFF00)
        mpu_ptr->extra_cycles += 1;
#endif

    return arg_and_y;
} // }}}

#endif
