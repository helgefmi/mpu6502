#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>

class Memory
{
    public:
        ~Memory()
        {
            if (memory)
                delete [] memory;
        }

        inline void setByte(uint16_t, uint8_t);
        inline void setWord(uint16_t, uint16_t);
        inline int8_t byteAt(uint16_t);
        inline int16_t wordAt(uint16_t);

        inline void reset();

        inline int getSize();
        inline void setSize(int);
    protected:
        uint8_t *memory;
        int size;
};

/* inlines */
inline int8_t Memory::byteAt(uint16_t offset) // {{{
{
    return memory[offset];
} // }}}
inline int16_t Memory::wordAt(uint16_t offset) // {{{
{
    return *((int16_t*)(memory + offset));
} // }}}
inline void Memory::setByte(uint16_t offset, uint8_t value) // {{{
{
    memory[offset] = value;
} // }}}
inline void Memory::setWord(uint16_t offset, uint16_t value) // {{{
{
    *((uint16_t*)(memory + offset)) = value;
} // }}}

inline void Memory::reset() // {{{
{
    for (int i = 0; i < size; ++i)
        memory[i] = '\0';
} // }}}

inline int Memory::getSize() // {{{
{
    return size;
} // }}}
inline void Memory::setSize(int size) // {{{
{
    this->size = size;
} // }}}

#endif
