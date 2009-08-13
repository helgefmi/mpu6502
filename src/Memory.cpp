#include "Memory.h"
#include <istream>

void Memory::copy_from_istream(std::istream &ifs)
{
    int size = ifs.tellg();
    ifs.seekg(0, std::iostream::beg);
    ifs.read((char*) memory, size);
}
