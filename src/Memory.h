#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>
#include <istream>
#include <cstring>
#include <map>

typedef void (*write_callback_t)(const uint16_t, const uint8_t);
typedef uint8_t (*read_callback_t)(const uint16_t);

class Memory
{
    public:
        Memory(unsigned int size) : size(size)
        {
            memory_ptr = new uint8_t[size];
            reset();
        }

        ~Memory()
        {
            delete [] memory_ptr;
        }

        inline void set_byte(const uint16_t, const uint8_t);
        inline void set_word(const uint16_t, const uint16_t);
        inline uint8_t get_byte(const uint16_t);
        inline uint16_t get_word(const uint16_t);

        void subscribe_to_write(uint16_t, uint16_t, write_callback_t);
        void subscribe_to_read(uint16_t, uint16_t, read_callback_t);

        inline void reset();
        inline void copy_from_istream(std::istream &ifs, uint16_t);

        inline int get_size() const;
    private:
        uint8_t *memory_ptr;
        int size;
        std::map<uint16_t, write_callback_t> write_callbacks;
        std::map<uint16_t, read_callback_t> read_callbacks;
};

/* inlines */
inline uint8_t Memory::get_byte(const uint16_t offset) // {{{
{
    if (read_callbacks.count(offset) > 0)
    {
        read_callback_t &callback = read_callbacks[offset];
        return callback(offset);
    }
    return memory_ptr[offset];
} // }}}
inline uint16_t Memory::get_word(const uint16_t offset) // {{{
{
    return get_byte(offset) + (get_byte(offset + 1) << 8);
} // }}}
inline void Memory::set_byte(const uint16_t offset, const uint8_t value) // {{{
{
    if (write_callbacks.count(offset) > 0)
    {
        write_callback_t &callback = write_callbacks[offset];
        callback(offset, value);
    }
    memory_ptr[offset] = value;
} // }}}
inline void Memory::set_word(const uint16_t offset, const uint16_t value) // {{{
{
    set_byte(offset, value & 0xFF);
    set_byte(offset + 1, value >> 8);
} // }}}

inline void Memory::subscribe_to_write(uint16_t from_offset, uint16_t area, write_callback_t fp) // {{{
{
    while (area)
    {
        write_callbacks[(--area) + from_offset] = fp;
    }
} // }}}
inline void Memory::subscribe_to_read(uint16_t from_offset, uint16_t area, read_callback_t fp) // {{{
{
    while (area)
    {
        read_callbacks[(--area) + from_offset] = fp;
    }
} // }}}
inline void Memory::reset() // {{{
{
    memset(memory_ptr, 0, size);
} // }}}
inline void Memory::copy_from_istream(std::istream &ifs, uint16_t org) // {{{
{
    int size = ifs.tellg();
    ifs.seekg(0, std::iostream::beg);
    ifs.read(((char*) memory_ptr + org), size);
} // }}}

inline int Memory::get_size() const // {{{
{
    return size;
} // }}}

#endif
