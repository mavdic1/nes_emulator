#include "Memory.h"
#include "Types.h"

void Memory::Initialize() //Initialize memory (set all values to 0)
{
    for (Byte &i : Data)
        i = 0;
}

void Memory::Write(Word address, Byte value) //Allows writing
{
    if (address >= 0x0800 && address <= 0x1FFF)
        Data[address & 0x07FF] = value; //Handle mirroring
    else
        Data[address] = value;
}

Byte Memory::Read(Word address) const //Allows reading
{
    if (address >= 0x0800 && address <= 0x1FFF)
        return Data[address & 0x07FF]; //Handle mirroring

    return Data[address];
}
