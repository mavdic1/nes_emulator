#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    Word addrZPX( CPU& cpu, const Memory& mem, int32& cycles)
    {
        Byte baseAddress = cpu.fetchByte(mem, cycles);
        CPU::consumeCycle(cycles);
        return static_cast<Byte>(baseAddress + cpu.X);
    }

    Word addrZPY(CPU& cpu, const Memory& mem, int32& cycles) {
        Byte base = cpu.fetchByte(mem, cycles);
        CPU::consumeCycle(cycles);
        return static_cast<Byte>(base + cpu.Y); // Use Y instead of X
    }

    Word addrABSX( CPU& cpu, const Memory& mem, int32& cycles, bool alwaysPenalty)
    {
        Word baseAddress = cpu.fetchWord(mem, cycles);
        Word finalAddress = baseAddress + cpu.X;

        if ((finalAddress & 0xFF00) != (baseAddress & 0xFF00) || alwaysPenalty)
            CPU::consumeCycle(cycles);

        return finalAddress;
    }

    Word addrABSY(CPU& cpu, const Memory& mem, int32& cycles, bool alwaysPenalty) {
        Word baseAddress = cpu.fetchWord(mem, cycles);
        Word finalAddress = baseAddress + cpu.Y;

        if ((finalAddress & 0xFF00) != (baseAddress & 0xFF00) || alwaysPenalty)
            CPU::consumeCycle(cycles);

        return finalAddress;
    }

    Word addrINDX(CPU& cpu, const Memory& mem, int32& cycles) {
        Byte base = cpu.fetchByte(mem, cycles);
        Byte loPtr = base + cpu.X;
        Byte hiPtr = static_cast<Byte>(loPtr + 1);;
        CPU::consumeCycle(cycles);

        Word lo = CPU::readByte(mem,cycles,loPtr);
        Word hi = CPU::readByte(mem,cycles,hiPtr);

        return (hi << 8) | lo;
    }

    Word addrINDY(CPU& cpu, const Memory& mem, int32& cycles, bool alwaysPenalty) {
        Byte base = cpu.fetchByte(mem, cycles);
        Byte loPtr = base;
        Byte hiPtr = static_cast<Byte>(loPtr + 1);;

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
}