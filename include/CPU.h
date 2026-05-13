#pragma once
#include "Types.h"
#include "Bus.h"

struct Bus;

struct CPU
{
    Bus* bus = nullptr;

    // Connect the CPU to a bus
    void ConnectBus(Bus* nBus) { bus = nBus; }

    Word PC{}; //Program Counter

    Byte S{}; //Stack

    Byte A{},X{},Y{}; //Registers
    Byte P{}; //Status register

    enum Flags
    {
        C = (1 << 0), Z = (1 << 1), I = (1 << 2), D = (1 << 3),
        B = (1 << 4), U = (1 << 5), V = (1 << 6), N = (1 << 7)
    };

    void setFlag(Flags flag, bool condition) {
        if (condition) P |= flag;
        else P &= ~flag;
    }

    void reset(Bus& bus); //Reset function
    static void consumeCycle(int32& cycles);

    Byte fetchByte(const Bus& bus, int32& cycles); //Fetches byte from Bus
    static Byte readByte(const Bus& bus, int32& cycles, Word address); //Fetches byte at specific address
    static void writeByte(Bus& bus, int32& cycles, Word address, Byte value);

    Word fetchWord(const Bus& bus, int32& cycles); //Fetches word from Bus
    static Word readWord(const Bus& bus, int32& cycles, Word address); //Fetches word at specific address
    static Word readWordPageWrap(const Bus& bus, int32& cycles, Word address);

    void execute(Bus& bus, int32 cycles); //Executes instruction based on opcode

};
