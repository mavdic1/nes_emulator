#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Internal helper
    static void Transfer_Execute(CPU &cpu, int32 &cycles, Byte &leftSide, const Byte &rightSide,
                                 bool updateFlagger = false) {
        leftSide = rightSide;
        CPU::consumeCycle(cycles);

        if (!updateFlagger) {
            cpu.setFlag(CPU::Z, (leftSide == 0));
            cpu.setFlag(CPU::N, (leftSide & 0x80) != 0);
        }
    }

    // Transfer A to X
    void TAX_func(CPU &cpu, int32 &cycles) {
        Transfer_Execute(cpu, cycles, cpu.X, cpu.A);
    }

    // Transfer A to Y
    void TAY_func(CPU &cpu, int32 &cycles) {
        Transfer_Execute(cpu, cycles, cpu.Y, cpu.A);
    }

    // Transfer Stack to X
    void TSX_func(CPU &cpu, int32 &cycles) {
        Transfer_Execute(cpu, cycles, cpu.X, cpu.S);
    }

    // Transfer X to A
    void TXA_func(CPU &cpu, int32 &cycles) {
        Transfer_Execute(cpu, cycles, cpu.A, cpu.X);
    }

    // Transfer X to Stack
    void TXS_func(CPU &cpu, int32 &cycles) {
        Transfer_Execute(cpu, cycles, cpu.S, cpu.X, true);
    }

    // Transfer Y to A
    void TYA_func(CPU &cpu, int32 &cycles) {
        Transfer_Execute(cpu, cycles, cpu.A, cpu.Y);
    }
}
