#include <iostream>
#include "include/Types.h"
#include "include/Memory.h"
#include "include/CPU.h"
#include "src/Instructions/Instructions.h"

int main()
{
    CPU cpu{};
    Memory mem{};

    mem.Initialize();

    //Inline test code - Start

    mem.Write(0x8000, Instructions::LDA_IMM);
    mem.Write(0x8001, 0x42);

    mem.Write(0xFFFC, 0x00);
    mem.Write(0xFFFD, 0x80);

    //Inline test code - End

    cpu.reset(mem);
    cpu.execute(mem, 2);

    return 0;
}