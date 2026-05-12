#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Push Accumulator
    void PHA_func(CPU &cpu, Memory &mem, int32 &cycles) {
        CPU::consumeCycle(cycles);
        CPU::writeByte(mem, cycles, 0x0100 + cpu.S, cpu.A);
        cpu.S--;
    }

    // Pull Accumulator
    void PLA_func(CPU &cpu, Memory &mem, int32 &cycles) {
        CPU::consumeCycle(cycles);
        cpu.S++;
        CPU::consumeCycle(cycles);

        cpu.A = CPU::readByte(mem, cycles, 0x0100 + cpu.S);
        cpu.setFlag(CPU::Z, (cpu.A == 0));
        cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
    }

    // Push Processor Status
    void PHP_func(CPU &cpu, Memory &mem, int32 &cycles) {
        CPU::consumeCycle(cycles);
        Byte status = cpu.P | CPU::B | CPU::U;
        CPU::writeByte(mem, cycles, 0x0100 + cpu.S, status);
        cpu.S--;
    }

    // Pull Processor Status
    void PLP_func(CPU &cpu, Memory &mem, int32 &cycles) {
        CPU::consumeCycle(cycles);
        cpu.S++;
        CPU::consumeCycle(cycles);

        Byte pulledP = CPU::readByte(mem, cycles, 0x0100 + cpu.S);
        cpu.P = (pulledP & 0xEF) | CPU::U;
    }
}
