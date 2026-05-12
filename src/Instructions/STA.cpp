#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Internal helper
    static void STA_Execute(Memory &mem, const CPU &cpu, int32 &cycles, Word address) {
        CPU::writeByte(mem, cycles, address, cpu.A);
    }

    // STA Zero Page
    void STA_ZP_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Byte address = cpu.fetchByte(mem, cycles);
        STA_Execute(mem, cpu, cycles, address);
    }

    // STA Zero Page X
    void STA_ZPX_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Byte address = addrZPX(cpu, mem, cycles);
        STA_Execute(mem, cpu, cycles, address);
    }

    // STA Absolute
    void STA_ABS_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        STA_Execute(mem, cpu, cycles, address);
    }

    // STA Absolute,X
    void STA_ABSX_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrABSX(cpu, mem, cycles, true);
        STA_Execute(mem, cpu, cycles, address);
    }

    // STA Absolute,Y
    void STA_ABSY_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrABSY(cpu, mem, cycles, true);
        STA_Execute(mem, cpu, cycles, address);
    }

    // STA Indirect,X
    void STA_INDX_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrINDX(cpu, mem, cycles);
        STA_Execute(mem, cpu, cycles, address);
    }

    // STA Indirect,Y
    void STA_INDY_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrINDY(cpu, mem, cycles, true);
        STA_Execute(mem, cpu, cycles, address);
    }
}
