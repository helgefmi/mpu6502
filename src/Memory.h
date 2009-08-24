#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>
#include <istream>
#include <cstring>

class Memory
{
    public:
        Memory(unsigned int size) : size(size)
        {
            memory = new uint8_t[size];
            reset();
        }

        ~Memory()
        {
            delete [] memory;
        }

        inline void set_byte(const uint16_t, const uint8_t);
        inline void set_word(const uint16_t, const uint16_t);
        inline uint8_t get_byte(const uint16_t) const;
        inline uint16_t get_word(const uint16_t) const;

        inline void reset();
        inline void copy_from_istream(std::istream &ifs);

        inline int get_size() const;
    private:
        uint8_t *memory;
        int size;
};

/* inlines */
inline uint8_t Memory::get_byte(const uint16_t offset) const // {{{
{
    return memory[offset];
} // }}}
inline uint16_t Memory::get_word(const uint16_t offset) const // {{{
{
    return get_byte(offset) + (get_byte(offset + 1) << 8);
} // }}}
inline void Memory::set_byte(const uint16_t offset, const uint8_t value) // {{{
{
    memory[offset] = value;
} // }}}
inline void Memory::set_word(const uint16_t offset, const uint16_t value) // {{{
{
    memory[offset] = value & 0xFF;
    memory[offset+1] = value >> 8;
} // }}}

inline void Memory::reset() // {{{
{
    memset(memory, 0, size);
} // }}}
inline void Memory::copy_from_istream(std::istream &ifs) // {{{
{
    int size = ifs.tellg();
    ifs.seekg(0, std::iostream::beg);
    ifs.read((char*) memory, size);
} // }}}

inline int Memory::get_size() const // {{{
{
    return size;
} // }}}

#endif
