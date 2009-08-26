#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H

#include <exception>
#include <string>
#include <sstream>

class InvalidOpcodeException : public std::exception
{
    public:
        InvalidOpcodeException(const int opcode) : opcode(opcode) {};
        std::string what()
        {
            std::stringstream ss;
            ss << "Invalid OpCode: 0x";
            ss << std::hex << opcode;
            return ss.str();
        }

        inline int get_opcode()
        {
            return opcode;
        }

    private:
        const int opcode;
};
#endif
