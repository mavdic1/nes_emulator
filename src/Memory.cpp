#include "Memory.h"
#include "Types.h"

void Memory::Initialize() //Initialize memory (set all values to 0)
{
    for (Byte &i : Data)
        i = 0;
}

Byte& Memory::operator[](Word address) //Allows writing
{
    if (address >= 0x0800 && address <= 0x1FFF)
        return Data[address & 0x07FF]; //Handle mirroring

    return Data[address];
}

const Byte& Memory::operator[](Word address) const //Allows reading
{
    if (address >= 0x0800 && address <= 0x1FFF)
        return Data[address & 0x07FF]; //Handle mirroring

    return Data[address];
}
