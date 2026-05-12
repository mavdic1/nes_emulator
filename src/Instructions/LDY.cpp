#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {

    // Internal helper
    static void LDY_Execute(CPU& cpu, Byte value) {
        cpu.Y = value;
        cpu.setFlag(CPU::Z, (cpu.Y == 0));
        cpu.setFlag(CPU::N, (cpu.Y & 0x80) != 0);
    }

    // LDY Immediate
    void LDY_IMM_func(CPU& cpu, Memory& mem, int32& cycles) {
        Byte value = cpu.fetchByte(mem, cycles);
        LDY_Execute(cpu, value);
    }

    // LDY Zero Page
    void LDY_ZP_func(CPU& cpu, Memory& mem, int32& cycles) {
        Byte address = cpu.fetchByte(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        LDY_Execute(cpu, value);
    }

    // LDY Zero Page,X
    void LDY_ZPX_func(CPU& cpu, Memory& mem, int32& cycles) {
        Word address = addrZPX(cpu, mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        LDY_Execute(cpu, value);
    }

    // LDY Absolute
    void LDY_ABS_func(CPU& cpu, Memory& mem, int32& cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        LDY_Execute(cpu, value);
    }

    // LDY Absolute,X
    void LDY_ABSX_func(CPU& cpu, Memory& mem, int32& cycles) {
        Word address = addrABSX(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,address);
        LDY_Execute(cpu, value);
    }
}