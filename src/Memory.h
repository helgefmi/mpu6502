#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>

class Memory
{
    public:
        Memory(unsigned int size)
        {
            set_size(size);
            memory = new uint8_t[size];
            reset();
        }
        ~Memory()
        {
            if (memory)
                delete [] memory;
        }

        inline void set_byte(uint16_t, uint8_t);
        inline void set_word(uint16_t, uint16_t);
        inline uint8_t get_byte(uint16_t) const;
        inline uint16_t get_word(uint16_t) const;

        inline void reset();

        inline int getSize() const;
        inline void set_size(int);
    private:
        uint8_t *memory;
        int size;
};

/* inlines */
inline uint8_t Memory::get_byte(uint16_t offset) const // {{{
{
    return memory[offset];
} // }}}
inline uint16_t Memory::get_word(uint16_t offset) const // {{{
{
    return get_byte(offset) + (get_byte(offset + 1) << 8);
} // }}}
inline void Memory::set_byte(uint16_t offset, uint8_t value) // {{{
{
    memory[offset] = value;
} // }}}
inline void Memory::set_word(uint16_t offset, uint16_t value) // {{{
{
    memory[offset] = value & 0xFF;
    memory[offset+1] = value >> 8;
} // }}}

inline void Memory::reset() // {{{
{
    for (int i = 0; i < getSize(); ++i)
        memory[i] = 0;
} // }}}

inline int Memory::getSize() const // {{{
{
    return size;
} // }}}
inline void Memory::set_size(int size) // {{{
{
    this->size = size;
} // }}}

#endif
