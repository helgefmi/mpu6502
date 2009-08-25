#ifndef __Memory6502_H
#define __Memory6502_H

#include "Memory.h"
#include "Mpu6502.h"

class Memory6502 : public Memory
{
    public:
        Memory6502(Mpu6502 *mpu_ptr) : Memory(0x10000), mpu_ptr(mpu_ptr) { }

        inline uint8_t get_immediate() const;
        inline uint8_t get_zero_page() const;
        inline uint8_t get_zero_page_x() const;
        inline uint8_t get_zero_page_y() const;
        inline uint16_t get_absolute() const;
        inline uint16_t get_absolute_x() const;
        inline uint16_t get_absolute_y() const;
        inline uint16_t get_indirect_x() const;
        inline uint16_t get_indirect_y() const;
    private:
        Mpu6502 *mpu_ptr;
};

inline uint8_t Memory6502::get_immediate() const // {{{
{
    return get_byte(mpu_ptr->reg.pc);
} // }}}
inline uint8_t Memory6502::get_zero_page() const // {{{
{
    return get_byte(mpu_ptr->reg.pc);
} // }}}
inline uint8_t Memory6502::get_zero_page_x() const // {{{
{
    return mpu_ptr->reg.x + get_byte(mpu_ptr->reg.pc);
} // }}}
inline uint8_t Memory6502::get_zero_page_y() const // {{{
{
    return mpu_ptr->reg.y + get_byte(mpu_ptr->reg.pc);
} // }}}
inline uint16_t Memory6502::get_absolute() const // {{{
{
    return get_word(mpu_ptr->reg.pc);
} // }}}
inline uint16_t Memory6502::get_absolute_x() const // {{{
{
    uint16_t arg = get_word(mpu_ptr->reg.pc);
    uint16_t arg_and_x = arg + mpu_ptr->reg.x;

#if 0
    if (arg_and_x & 0xFF00 != arg & 0xFF00)
        mpu_ptr->extra_cycles += 1;
#endif

    return arg_and_x;
} // }}}
inline uint16_t Memory6502::get_absolute_y() const // {{{
{
    uint16_t arg = get_word(mpu_ptr->reg.pc);
    uint16_t arg_and_y = arg + mpu_ptr->reg.y;

#if 0
    if (arg_and_y & 0xFF00 != arg & 0xFF00)
        mpu_ptr->extra_cycles += 1;
#endif

    return arg_and_y;
} // }}}
inline uint16_t Memory6502::get_indirect_x() const // {{{
{
    return get_word(get_zero_page_x());
} // }}}
inline uint16_t Memory6502::get_indirect_y() const // {{{
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
