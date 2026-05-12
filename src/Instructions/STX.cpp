#include "Instructions.h"

namespace Instructions {

    // Internal helper
    static void STX_Execute(Memory& mem, CPU& cpu, u32& cycles, Word address)
    {
        CPU::writeByte(mem,cycles,address,cpu.X);
    }

    void RegisterSTX() {
        // STX Zero Page
        table[STX_ZP] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = cpu.fetchByte(mem, cycles);
            STX_Execute(mem, cpu, cycles,address);
        };

        // STX Zero Page Y
        table[STX_ZPY] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrZPY(cpu, mem, cycles);
            STX_Execute(mem, cpu, cycles,address);
        };

        // STX Absolute
        table[STX_ABS] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = cpu.fetchWord(mem, cycles);
            STX_Execute(mem, cpu, cycles,address);
        };
    }
}