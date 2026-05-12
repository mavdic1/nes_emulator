#include "CPU.h"
#include "Instructions/Instructions.h"

void CPU::reset(Memory& mem) //Reset function
{
    //mem.Initialize(); //Initialize memory

    const Word lo = mem[0xFFFC]; //Reset vector low
    const Word hi = mem[0xFFFD]; //Reset vector high
    PC = (hi << 8) | lo; //Set Program Counter to address from memory based on reset vector

    S = 0xFD; // Set the stack to NES standard location

    A = X = Y = 0; //Registers reset to 0 for safety

    P = I | U;

}

void CPU::consumeCycle(u32& cycles)
{
    if (cycles > 0) cycles--;
}

Byte CPU::fetchByte(const Memory& mem, u32& cycles) //Fetches byte from memory at current PC
{
    Byte Data = mem[PC];
    PC += 1;
    if (cycles > 0) cycles--;
    return Data;
}

Byte CPU::readByte(const Memory& mem, u32& cycles, Word address) //Fetches byte from memory at current PC
{
    Byte Data = mem[address];
    if (cycles > 0) cycles--;
    return Data;
}

void CPU::writeByte(Memory& mem, u32& cycles, Word address, Byte value)
{
    mem[address] = value;
    consumeCycle(cycles);
}

Word CPU::fetchWord(const Memory& mem, u32& cycles) //Fetches word from memory
{
    Word lo = fetchByte(mem, cycles);
    Word hi = fetchByte(mem, cycles);
    Word value = hi << 8 | lo;
    return value;
}

Word CPU::readWord(const Memory& mem, u32& cycles, Word address) //Fetches word at specific address
{
    Word lo = readByte(mem, cycles,address);
    Word hi = readByte(mem, cycles,address+1);
    Word value = hi << 8 | lo;
    return value;
}

Word CPU::readWordPageWrap(const Memory& mem, u32& cycles, Word address)
{
    Word lo = readByte(mem, cycles, address);
    Word hiAddress = (address & 0xFF00) | ((address + 1) & 0x00FF);
    Word hi = readByte(mem, cycles, hiAddress);

    return (hi << 8) | lo;
}

void CPU::execute(Memory& mem, u32 cycles) //Execute
{
    while (cycles > 0)
    {
        Byte opcode = fetchByte(mem, cycles); //Fetch opcode at PC

        if (const Instructions::InstrFunc instr = Instructions::table[opcode]) //Get instruction from table based on opcode
            instr(*this,mem,cycles); //If found execute
        else
            std::cerr << "Unknown opcode: " << std::hex << +opcode << " at: "<<PC<<"\n"; //Else throw error
    }

}