#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Internal helper
    static void Store_Execute(Memory &mem, const CPU &cpu, int32 &cycles, Word address, const Byte& reg) {
        CPU::writeByte(mem, cycles, address, reg);
    }

    /*
     * S
     * T
     * A
     */

    // STA Zero Page
    void STA_ZP_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Byte address = cpu.fetchByte(mem, cycles);
        Store_Execute(mem, cpu, cycles, address, cpu.A);
    }

    // STA Zero Page X
    void STA_ZPX_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Byte address = addrZPX(cpu, mem, cycles);
        Store_Execute(mem, cpu, cycles, address, cpu.A);
    }

    // STA Absolute
    void STA_ABS_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        Store_Execute(mem, cpu, cycles, address, cpu.A);
    }

    // STA Absolute,X
    void STA_ABSX_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrABSX(cpu, mem, cycles, true);
        Store_Execute(mem, cpu, cycles, address, cpu.A);
    }

    // STA Absolute,Y
    void STA_ABSY_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrABSY(cpu, mem, cycles, true);
        Store_Execute(mem, cpu, cycles, address, cpu.A);
    }

    // STA Indirect,X
    void STA_INDX_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrINDX(cpu, mem, cycles);
        Store_Execute(mem, cpu, cycles, address, cpu.A);
    }

    // STA Indirect,Y
    void STA_INDY_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrINDY(cpu, mem, cycles, true);
        Store_Execute(mem, cpu, cycles, address, cpu.A);
    }

    /*
     * S
     * T
     * X
     */

    // STX Zero Page
    void STX_ZP_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = cpu.fetchByte(mem, cycles);
        Store_Execute(mem, cpu, cycles, address, cpu.X);
    }

    // STX Zero Page Y
    void STX_ZPY_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrZPY(cpu, mem, cycles);
        Store_Execute(mem, cpu, cycles, address, cpu.X);
    }

    // STX Absolute
    void STX_ABS_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        Store_Execute(mem, cpu, cycles, address, cpu.X);
    }

    /*
     * S
     * T
     * Y
     */
    
    void STY_ZP_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = cpu.fetchByte(mem, cycles);
        Store_Execute(mem, cpu, cycles, address, cpu.Y);
    }

    // STY Zero Page X
    void STY_ZPX_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = addrZPX(cpu, mem, cycles);
        Store_Execute(mem, cpu, cycles, address, cpu.Y);
    }

    // STY Absolute
    void STY_ABS_func(CPU &cpu, Memory &mem, int32 &cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        Store_Execute(mem, cpu, cycles, address, cpu.Y);
    }
}
