#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {

    // Internal helper
    static void LDA_Execute(CPU& cpu, Byte value) {
        cpu.A = value;
        cpu.setFlag(CPU::Z, (cpu.A == 0));
        cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
    }
    
    // LDA Immediate
    void LDA_IMM_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Byte value = cpu.fetchByte(mem, cycles);
        LDA_Execute(cpu, value);
    }
    
    // LDA Zero Page
    void LDA_ZP_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Byte address = cpu.fetchByte(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        LDA_Execute(cpu, value);
    }

    // LDA Zero Page X
    void LDA_ZPX_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = addrZPX(cpu, mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        LDA_Execute(cpu, value);
    }

    // LDA Absolute
    void LDA_ABS_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        LDA_Execute(cpu, value);
    }

    // LDA Absolute,X
    void LDA_ABSX_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = addrABSX(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,address);
        LDA_Execute(cpu, value);
    }

    // LDA Absolute,Y
    void LDA_ABSY_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = addrABSY(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,address);
        LDA_Execute(cpu, value);
    }

    // LDA Indirect,X
    void LDA_INDX_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word targetAddress = addrINDX(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,targetAddress);

        LDA_Execute(cpu, value);
    }

    //LDA Indirect,Y
    void LDA_INDY_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word targetAddress = addrINDY(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,targetAddress);

        LDA_Execute(cpu, value);
    }
}
