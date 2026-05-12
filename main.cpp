#include <iostream>
#include "include/Types.h"
#include "include/Memory.h"
#include "include/CPU.h"
#include "src/Instructions/Instructions.h"

int main()
{
    CPU cpu{};
    Memory mem;

    mem.Initialize();
    Instructions::InitializeTable();

    //Inline test code - Start

    mem[0x8000] = Instructions::LDA_IMM;
    mem[0x8001] = 0x42;

    mem[0xFFFC] = 0x00; // Low byte
    mem[0xFFFD] = 0x80; // High byte (0x8000)

    //Inline test code - End

    cpu.reset(mem);
    cpu.execute(mem, 3);

    return 0;
}