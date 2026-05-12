#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Internal helper
    static void STY_Execute(Memory &mem, const CPU &cpu, int32 &cycles, Word address) {
        CPU::writeByte(mem, cycles, address, cpu.Y);
    }

    // STY Zero Page
    void STY_ZP_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = cpu.fetchByte(mem, cycles);
        STY_Execute(mem, cpu, cycles, address);
    }

    // STY Zero Page X
    void STY_ZPX_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrZPX(cpu, mem, cycles);
        STY_Execute(mem, cpu, cycles, address);
    }

    // STY Absolute
    void STY_ABS_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        STY_Execute(mem, cpu, cycles, address);
    }
}
