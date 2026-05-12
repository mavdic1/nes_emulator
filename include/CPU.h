#pragma once
#include <cstdint>
#include <iostream>

#include "Types.h"
#include "Memory.h"

struct CPU
{
    Word PC; //Program Counter

    Byte S; //Stack

    Byte A,X,Y; //Registers
    Byte P; //Status register

    enum Flags
    {
        C = (1 << 0), Z = (1 << 1), I = (1 << 2), D = (1 << 3),
        B = (1 << 4), U = (1 << 5), V = (1 << 6), N = (1 << 7)
    };

    void setFlag(Flags flag, bool condition) {
        if (condition) P |= flag;
        else P &= ~flag;
    }

    void reset(Memory& mem); //Reset function
    static void consumeCycle(u32& cycles);

    Byte fetchByte(const Memory& mem, u32& cycles); //Fetches byte from memory
    static Byte readByte(const Memory& mem, u32& cycles, Word address); //Fetches byte at specific address
    static void writeByte(Memory& mem, u32& cycles, Word address, Byte value);

    Word fetchWord(const Memory& mem, u32& cycles); //Fetches word from memory
    static Word readWord(const Memory& mem, u32& cycles, Word address); //Fetches word at specific address
    static Word readWordPageWrap(const Memory& mem, u32& cycles, Word address);

    void execute(Memory& mem, u32 cycles); //Executes instruction based on opcode

};