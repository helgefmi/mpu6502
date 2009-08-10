#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>

class Memory
{
    public:
        Memory(unsigned int size)
        {
            setSize(size);
            memory = new int8_t[size];
            reset();
        }
        ~Memory()
        {
            if (memory)
                delete [] memory;
        }

        inline void setByte(uint16_t, int8_t);
        inline void setWord(uint16_t, int16_t);
        inline int8_t byteAt(uint16_t);
        inline int16_t wordAt(uint16_t);

        inline void reset();

        inline int getSize();
        inline void setSize(int);
    private:
        int8_t *memory;
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
inline void Memory::setByte(uint16_t offset, int8_t value) // {{{
{
    memory[offset] = value;
} // }}}
inline void Memory::setWord(uint16_t offset, int16_t value) // {{{
{
    *((int16_t*)(memory + offset)) = value;
} // }}}

inline void Memory::reset() // {{{
{
    for (int i = 0; i < getSize(); ++i)
        memory[i] = 0;
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
