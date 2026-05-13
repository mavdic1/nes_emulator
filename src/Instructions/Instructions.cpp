#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    Word addrIMM(CPU& cpu) {
        Word address = cpu.PC;
        cpu.PC++;
        return address;
    }

    Word addrZP(CPU& cpu, const Bus& Bus, int32& cycles) {
        return cpu.fetchByte(Bus, cycles); // Returns 0x00 to 0xFF
    }

    Word addrZPX( CPU& cpu, const Bus& Bus, int32& cycles)
    {
        Byte baseAddress = cpu.fetchByte(Bus, cycles);
        CPU::consumeCycle(cycles);
        return static_cast<Byte>(baseAddress + cpu.X);
    }

    Word addrZPY(CPU& cpu, const Bus& Bus, int32& cycles) {
        Byte base = cpu.fetchByte(Bus, cycles);
        CPU::consumeCycle(cycles);
        return static_cast<Byte>(base + cpu.Y); // Use Y instead of X
    }

    Word addrABS(CPU& cpu, const Bus& Bus, int32& cycles) {
        return cpu.fetchWord(Bus, cycles);
    }

    Word addrABSX( CPU& cpu, const Bus& Bus, int32& cycles, bool alwaysPenalty)
    {
        Word baseAddress = cpu.fetchWord(Bus, cycles);
        Word finalAddress = baseAddress + cpu.X;

        if ((finalAddress & 0xFF00) != (baseAddress & 0xFF00) || alwaysPenalty)
            CPU::consumeCycle(cycles);

        return finalAddress;
    }

    Word addrABSY(CPU& cpu, const Bus& Bus, int32& cycles, bool alwaysPenalty) {
        Word baseAddress = cpu.fetchWord(Bus, cycles);
        Word finalAddress = baseAddress + cpu.Y;

        if ((finalAddress & 0xFF00) != (baseAddress & 0xFF00) || alwaysPenalty)
            CPU::consumeCycle(cycles);

        return finalAddress;
    }

    Word addrIND(CPU& cpu, const Bus& Bus, int32& cycles) {
        Word ptrAddress = cpu.fetchWord(Bus, cycles);
        return CPU::readWordPageWrap(Bus, cycles, ptrAddress);
    }

    Word addrINDX(CPU& cpu, const Bus& Bus, int32& cycles) {
        Byte base = cpu.fetchByte(Bus, cycles);
        Byte loPtr = base + cpu.X;
        Byte hiPtr = static_cast<Byte>(loPtr + 1);;
        CPU::consumeCycle(cycles);

        Word lo = CPU::readByte(Bus,cycles,loPtr);
        Word hi = CPU::readByte(Bus,cycles,hiPtr);

        return (hi << 8) | lo;
    }

    Word addrINDY(CPU& cpu, const Bus& Bus, int32& cycles, bool alwaysPenalty) {
        Byte base = cpu.fetchByte(Bus, cycles);
        Byte loPtr = base;
        Byte hiPtr = static_cast<Byte>(loPtr + 1);;

        Word lo = CPU::readByte(Bus,cycles,loPtr);
        Word hi = CPU::readByte(Bus,cycles,hiPtr);

        Word baseAddress = (hi << 8) | lo;
        Word finalAddress = baseAddress + cpu.Y;

        // 4. Page Crossing Penalty: If the high byte changes, it costs 1 extra cycle
        if ((finalAddress & 0xFF00) != (baseAddress & 0xFF00) || alwaysPenalty) {
            CPU::consumeCycle(cycles);
        }

        return finalAddress;
    }
}
