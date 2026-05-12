#pragma once
#include <cstdint>
#include "../../include/Types.h"
#include "../../include/CPU.h"
#include "../../include/Memory.h"

/*
 * IMM - Immediate
 * ZP - Zero Page
 * ZPX - Zero Page,X
 * ABS - Absolute
 * ABSX - Absolute,X
 * ABSY - Absolute,Y
 * INDX - (Indirect,X)
 * INDY - (Indirect),Y
 */

//Opcodes contained in ./include/Types.h

namespace Instructions {
    //Setup
    using InstrFunc = void (*)(CPU& cpu, Memory& mem, u32& cycles);
    extern InstrFunc table[256]; // Use 'extern' because the table lives in a .cpp file

    //Common functions
    inline Word addrZPX( CPU& cpu, Memory& mem, u32& cycles)
    {
        Byte baseAddress = cpu.fetchByte(mem, cycles);
        CPU::consumeCycle(cycles);
        return static_cast<Byte>(baseAddress + cpu.X);
    }

    inline Word addrZPY(CPU& cpu, Memory& mem, u32& cycles) {
        Byte base = cpu.fetchByte(mem, cycles);
        CPU::consumeCycle(cycles);
        return static_cast<Byte>(base + cpu.Y); // Use Y instead of X
    }

    inline Word addrABSX( CPU& cpu, Memory& mem, u32& cycles, bool alwaysPenalty=false)
    {
        Word baseAddress = cpu.fetchWord(mem, cycles);
        Word finalAddress = baseAddress + cpu.X;

        if ((finalAddress & 0xFF00) != (baseAddress & 0xFF00) || alwaysPenalty)
            CPU::consumeCycle(cycles);

        return finalAddress;
    }

    inline Word addrABSY(CPU& cpu, Memory& mem, u32& cycles, bool alwaysPenalty = false) {
        Word baseAddress = cpu.fetchWord(mem, cycles);
        Word finalAddress = baseAddress + cpu.Y;

        if ((finalAddress & 0xFF00) != (baseAddress & 0xFF00) || alwaysPenalty)
            CPU::consumeCycle(cycles);

        return finalAddress;
    }

    inline Word addrINDX(CPU& cpu, Memory& mem, u32& cycles) {
        Byte base = cpu.fetchByte(mem, cycles);
        Byte loPtr = base + cpu.X;
        Byte hiPtr = loPtr+1;
        CPU::consumeCycle(cycles);

        Word lo = CPU::readByte(mem,cycles,loPtr);
        Word hi = CPU::readByte(mem,cycles,hiPtr);

        return (hi << 8) | lo;
    }

    inline Word addrINDY(CPU& cpu, Memory& mem, u32& cycles, bool alwaysPenalty = false) {
        Byte base = cpu.fetchByte(mem, cycles);
        Byte loPtr = base;
        Byte hiPtr = loPtr+1;

        Word lo = CPU::readByte(mem,cycles,loPtr);
        Word hi = CPU::readByte(mem,cycles,hiPtr);

        Word baseAddress = (hi << 8) | lo;
        Word finalAddress = baseAddress + cpu.Y;

        // 4. Page Crossing Penalty: If the high byte changes, it costs 1 extra cycle
        if ((finalAddress & 0xFF00) != (baseAddress & 0xFF00) || alwaysPenalty) {
            CPU::consumeCycle(cycles);
        }

        return finalAddress;
    }


    // Prototypes for registration functions
    void RegisterLDA();
    void RegisterLDX();
    void RegisterLDY();

    void RegisterSTA();
    void RegisterSTX();
    void RegisterSTY();

    inline void InitializeTable() {
        // Clear table
        for (auto& i : table) i = nullptr;

        // Call each group's registration
        RegisterLDA();
        RegisterLDX();
        RegisterLDY();

        RegisterSTA();
        RegisterSTX();
        RegisterSTY();
    }
}