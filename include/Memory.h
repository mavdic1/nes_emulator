#pragma once
#include <cstdint>
#include <iostream>

#include "Types.h"

struct Memory
{
    static constexpr u32 MAX_MEM = 64 * 1024;
    Byte Data[MAX_MEM]{};

    void Initialize(); //Initialize memory (set all values to 0)

    Byte& operator[]( Word address); //Allows writing
    const Byte& operator[]( Word address) const; //Allows reading
};
