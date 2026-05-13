#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {

    void JMP(CPU& cpu, const Bus& Bus, int32& cycles, const AddrMode mode) {
        Word targetAddress;
        if (mode == AddrMode::ABS)
            targetAddress = addrABS(cpu, Bus, cycles);
        else
            targetAddress = addrIND(cpu, Bus, cycles);
        cpu.PC = targetAddress;
    }

    void JSR(CPU& cpu, Bus& Bus, int32& cycles) {
        Word targetAddress = addrABS(cpu, Bus, cycles);
        CPU::consumeCycle(cycles);

        Word returnAddress = cpu.PC - 1;

        CPU::writeByte(Bus, cycles, 0x0100 + cpu.S, (returnAddress >> 8) & 0xFF);
        cpu.S--;

        CPU::writeByte(Bus, cycles, 0x0100 + cpu.S, returnAddress & 0xFF);
        cpu.S--;

        cpu.PC = targetAddress;
    }

    void RTS_func(CPU& cpu, Bus& Bus, int32& cycles) {
        CPU::consumeCycle(cycles);

        cpu.S++;
        CPU::consumeCycle(cycles);

        Word lo = CPU::readByte(Bus, cycles, 0x0100 + cpu.S);

        cpu.S++;
        Word hi = CPU::readByte(Bus, cycles, 0x0100 + cpu.S);

        Word address = (hi << 8) | lo;

        cpu.PC = address + 1;
        CPU::consumeCycle(cycles);
    }
}
