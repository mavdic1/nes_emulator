#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {

    // NOP - No Operation (2 cycles)
    void NOP_func(CPU& cpu, int32& cycles) {
        CPU::consumeCycle(cycles);
    }

    // BIT - Bit Test
    void BIT(CPU& cpu, const Bus& Bus, int32& cycles, AddrMode mode) {
        Word address;
        if (mode == AddrMode::ZP) address = addrZP(cpu, Bus, cycles);
        else address = addrABS(cpu, Bus, cycles);

        Byte val = CPU::readByte(Bus, cycles, address);

        cpu.setFlag(CPU::Z, (cpu.A & val) == 0);
        cpu.setFlag(CPU::N, (val & (1 << 7)) != 0);
        cpu.setFlag(CPU::V, (val & (1 << 6)) != 0);
    }

    // BRK - Force Interrupt
    void BRK_func(CPU& cpu, Bus& Bus, int32& cycles) {
        Word pcToPush = cpu.PC + 1;

        CPU::writeByte(Bus, cycles, 0x0100 + cpu.S, (pcToPush >> 8) & 0xFF);
        cpu.S--;
        CPU::writeByte(Bus, cycles, 0x0100 + cpu.S, pcToPush & 0xFF);
        cpu.S--;

        Byte status = cpu.P | CPU::B | CPU::U;
        CPU::writeByte(Bus, cycles, 0x0100 + cpu.S, status);
        cpu.S--;

        cpu.setFlag(CPU::I, true);

        cpu.PC = CPU::readWord(Bus, cycles, 0xFFFE);
    }

    // RTI - Return from Interrupt
    void RTI_func(CPU& cpu, Bus& Bus, int32& cycles) {
        CPU::consumeCycle(cycles); // Internal cycle

        cpu.S++;
        CPU::consumeCycle(cycles);
        Byte pulledP = CPU::readByte(Bus, cycles, 0x0100 + cpu.S);
        cpu.P = (pulledP & 0xEF) | CPU::U;

        cpu.S++;
        Word lo = CPU::readByte(Bus, cycles, 0x0100 + cpu.S);

        cpu.S++;
        Word hi = CPU::readByte(Bus, cycles, 0x0100 + cpu.S);

        cpu.PC = (hi << 8) | lo;
        
        CPU::consumeCycle(cycles);
    }
}