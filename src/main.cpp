#include "Mpu6502.h"
#include "exceptions.h"
#include <iostream>

using namespace std;

int main()
{
    Mpu6502 cpu;
    cout << cpu.to_string() << endl;

    try
    {
        cpu.tick();
    } catch (InvalidOpcodeException e)
    {
        cout << e.what() << endl;
        cout << cpu.to_string() << endl;
    }

    return 0;
}
