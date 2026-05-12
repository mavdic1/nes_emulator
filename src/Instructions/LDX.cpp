#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {

    // Internal helper
    static void LDX_Execute(CPU& cpu, Byte value) {
        cpu.X = value;
        cpu.setFlag(CPU::Z, (cpu.X == 0));
        cpu.setFlag(CPU::N, (cpu.X & 0x80) != 0);
    }

    // LDX Immediate
    void LDX_IMM_func(CPU& cpu, Memory& mem, int32& cycles) {
        Byte value = cpu.fetchByte(mem, cycles);
        LDX_Execute(cpu, value);
    }

    // LDX Zero Page
    void LDX_ZP_func(CPU& cpu, Memory& mem, int32& cycles) {
        Byte address = cpu.fetchByte(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        LDX_Execute(cpu, value);
    }

    // LDX Zero Page,Y
    void LDX_ZPY_func(CPU& cpu, Memory& mem, int32& cycles) {
        Word address = addrZPY(cpu, mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        LDX_Execute(cpu, value);
    }

        // LDX Absolute
    void LDX_ABS_func(CPU& cpu, Memory& mem, int32& cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        LDX_Execute(cpu, value);
    }

    // LDX Absolute,Y
    void LDX_ABSY_func(CPU &cpu, const Memory &mem, int32 &cycles) {
        Word address = addrABSY(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,address);
        LDX_Execute(cpu, value);
    }
}