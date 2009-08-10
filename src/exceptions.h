#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H

#include <exception>
#include <string>
#include <sstream>

class InvalidOpcodeException : public std::exception
{
    public:
        InvalidOpcodeException(int opcode) : opcode(opcode) {};
        std::string what()
        {
            std::stringstream ss;
            ss << "Invalid OpCode: ";
            ss << opcode;
            return ss.str();
        }

    private:
        int opcode;
};
#endif
