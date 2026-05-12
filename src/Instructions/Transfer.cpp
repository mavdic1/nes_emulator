#include "Instructions.h"

namespace Instructions {

    // Internal helper
    static void Transfer_Execute(CPU& cpu, u32& cycles, Byte& leftSide, const Byte& rightSide, bool updateFlagger=false) {
        leftSide = rightSide;
        CPU::consumeCycle(cycles);

        if (!updateFlagger) {
            cpu.setFlag(CPU::Z, (leftSide == 0));
            cpu.setFlag(CPU::N, (leftSide & 0x80) != 0);
        }
    }

    void RegisterTransfer() {
        // Transfer A to X
        table[TAX] = [](CPU& cpu, Memory& mem, u32& cycles)
        {
            Transfer_Execute(cpu, cycles, cpu.X, cpu.A);
        };

        // Transfer A to Y
        table[TAY] = [](CPU& cpu, Memory& mem, u32& cycles)
        {
            Transfer_Execute(cpu, cycles, cpu.Y, cpu.A);
        };

        // Transfer Stack to X
        table[TSX] = [](CPU& cpu, Memory& mem, u32& cycles)
        {
            Transfer_Execute(cpu, cycles, cpu.X, cpu.S);
        };

        // Transfer X to A
        table[TXA] = [](CPU& cpu, Memory& mem, u32& cycles)
        {
            Transfer_Execute(cpu, cycles, cpu.A, cpu.X);
        };

        // Transfer X to Stack
        table[TXS] = [](CPU& cpu, Memory& mem, u32& cycles)
        {
            Transfer_Execute(cpu, cycles, cpu.S, cpu.X, true);
        };

        // Transfer Y to A
        table[TYA] = [](CPU& cpu, Memory& mem, u32& cycles)
        {
            Transfer_Execute(cpu, cycles, cpu.A, cpu.Y);
        };
    }
}