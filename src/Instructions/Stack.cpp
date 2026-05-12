#include "Instructions.h"

namespace Instructions {

    void RegisterStack() {
        // Push Accumulator
        table[PHA] = [](CPU& cpu, Memory& mem, u32& cycles) {
            CPU::consumeCycle(cycles);
            CPU::writeByte(mem, cycles, 0x0100 + cpu.S, cpu.A);
            cpu.S--;
        };

        // Pull Accumulator
        table[PLA] = [](CPU& cpu, Memory& mem, u32& cycles) {
            CPU::consumeCycle(cycles);
            cpu.S++;
            CPU::consumeCycle(cycles);

            cpu.A = CPU::readByte(mem, cycles, 0x0100 + cpu.S);
            cpu.setFlag(CPU::Z, (cpu.A == 0));
            cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
        };

        // Push Processor Status
        table[PHP] = [](CPU& cpu, Memory& mem, u32& cycles) {
            CPU::consumeCycle(cycles);
            Byte status = cpu.P | CPU::B | CPU::U;
            CPU::writeByte(mem, cycles, 0x0100 + cpu.S, status);
            cpu.S--;
        };

        // Pull Processor Status
        table[PLP] = [](CPU& cpu, Memory& mem, u32& cycles) {
            CPU::consumeCycle(cycles);
            cpu.S++;
            CPU::consumeCycle(cycles);

            Byte pulledP = CPU::readByte(mem, cycles, 0x0100 + cpu.S);
            cpu.P = pulledP;
            cpu.setFlag(CPU::U, true);
            cpu.setFlag(CPU::B, false);
        };
    }
}