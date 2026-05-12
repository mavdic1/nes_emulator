#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Internal helper
    static void STX_Execute(Memory &mem, const CPU &cpu, int32 &cycles, Word address) {
        CPU::writeByte(mem, cycles, address, cpu.X);
    }

    // STX Zero Page
    void STX_ZP_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = cpu.fetchByte(mem, cycles);
        STX_Execute(mem, cpu, cycles, address);
    }

    // STX Zero Page Y
    void STX_ZPY_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrZPY(cpu, mem, cycles);
        STX_Execute(mem, cpu, cycles, address);
    }

    // STX Absolute
    void STX_ABS_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        STX_Execute(mem, cpu, cycles, address);
    }
}
