#include "Instructions.h"

namespace Instructions {

    // Internal helper
    static void LDX_Execute(CPU& cpu, Byte value) {
        cpu.X = value;
        cpu.setFlag(CPU::Z, (cpu.X == 0));
        cpu.setFlag(CPU::N, (cpu.X & 0x80) != 0);
    }

    void RegisterLDX() {
        // LDX Immediate
        table[LDX_IMM] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Byte value = cpu.fetchByte(mem, cycles);
            LDX_Execute(cpu, value);
        };

        // LDX Zero Page
        table[LDX_ZP] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Byte address = cpu.fetchByte(mem, cycles);
            Byte value = CPU::readByte(mem, cycles, address);
            LDX_Execute(cpu, value);
        };

        // LDX Zero Page,Y
        table[LDX_ZPY] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrZPY(cpu, mem, cycles);
            Byte value = CPU::readByte(mem, cycles, address);
            LDX_Execute(cpu, value);
        };

        // LDX Absolute
        table[LDX_ABS] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = cpu.fetchWord(mem, cycles);
            Byte value = CPU::readByte(mem, cycles, address);
            LDX_Execute(cpu, value);
        };

        // LDX Absolute,Y
        table[LDX_ABSY] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrABSY(cpu,mem,cycles);
            Byte value = CPU::readByte(mem,cycles,address);
            LDX_Execute(cpu, value);
        };
    }
}