#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>

class Memory
{
    public:
        Memory(unsigned int size)
        {
            setSize(size);
            memory = new uint8_t[size];
            reset();
        }
        ~Memory()
        {
            if (memory)
                delete [] memory;
        }

        inline void setByte(uint16_t, uint8_t);
        inline void setWord(uint16_t, uint16_t);
        inline uint8_t byteAt(uint16_t) const;
        inline uint16_t wordAt(uint16_t) const;

        inline void reset();

        inline int getSize() const;
        inline void setSize(int);
    private:
        uint8_t *memory;
        int size;
};

/* inlines */
inline uint8_t Memory::byteAt(uint16_t offset) const // {{{
{
    return memory[offset];
} // }}}
inline uint16_t Memory::wordAt(uint16_t offset) const // {{{
{
    return byteAt(offset) + (byteAt(offset + 1) << 8);
} // }}}
inline void Memory::setByte(uint16_t offset, uint8_t value) // {{{
{
    memory[offset] = value;
} // }}}
inline void Memory::setWord(uint16_t offset, uint16_t value) // {{{
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
inline void Memory::setSize(int size) // {{{
{
    this->size = size;
} // }}}

#endif
