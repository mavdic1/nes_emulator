#include "Instructions.h"

namespace Instructions {

    // Internal helper
    static void STY_Execute(Memory& mem, CPU& cpu, u32& cycles, Word address)
    {
        CPU::writeByte(mem,cycles,address,cpu.Y);
    }

    void RegisterSTY() {
        // STY Zero Page
        table[STY_ZP] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = cpu.fetchByte(mem, cycles);
            STY_Execute(mem, cpu, cycles,address);
        };

        // STY Zero Page X
        table[STY_ZPX] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrZPX(cpu, mem, cycles);
            STY_Execute(mem, cpu, cycles,address);
        };

        // STY Absolute
        table[STY_ABS] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = cpu.fetchWord(mem, cycles);
            STY_Execute(mem, cpu, cycles,address);
        };
    }
}