#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H

#include <exception>
#include <string>

class InvalidOpcodeException : public std::exception
{
    public:
        std::string what()
        {
            return "Invalid OpCode";
        }
};
#endif
