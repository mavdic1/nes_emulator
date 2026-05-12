#include "Instructions.h"

namespace Instructions {

    // Internal helper
    static void LDY_Execute(CPU& cpu, Byte value) {
        cpu.Y = value;
        cpu.setFlag(CPU::Z, (cpu.Y == 0));
        cpu.setFlag(CPU::N, (cpu.Y & 0x80) != 0);
    }

    void RegisterLDY() {
        // LDY Immediate
        table[LDY_IMM] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Byte value = cpu.fetchByte(mem, cycles);
            LDY_Execute(cpu, value);
        };

        // LDY Zero Page
        table[LDY_ZP] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Byte address = cpu.fetchByte(mem, cycles);
            Byte value = CPU::readByte(mem, cycles, address);
            LDY_Execute(cpu, value);
        };

        // LDY Zero Page,X
        table[LDY_ZPX] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrZPX(cpu, mem, cycles);
            Byte value = CPU::readByte(mem, cycles, address);
            LDY_Execute(cpu, value);
        };

        // LDY Absolute
        table[LDY_ABS] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = cpu.fetchWord(mem, cycles);
            Byte value = CPU::readByte(mem, cycles, address);
            LDY_Execute(cpu, value);
        };

        // LDY Absolute,X
        table[LDY_ABSX] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrABSX(cpu,mem,cycles);
            Byte value = CPU::readByte(mem,cycles,address);
            LDY_Execute(cpu, value);
        };
    }
}