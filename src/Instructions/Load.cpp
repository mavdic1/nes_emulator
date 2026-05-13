#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {

    // Internal helper
    static void Load_Execute(CPU& cpu, Byte value, Byte& reg) {
        reg = value;
        cpu.setFlag(CPU::Z, (reg == 0));
        cpu.setFlag(CPU::N, (reg & 0x80) != 0);
    }

    /*
     * L
     * D
     * A
     */
    
    // LDA Immediate
    void LDA_IMM_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Byte value = cpu.fetchByte(mem, cycles);
        Load_Execute(cpu, value, cpu.A);
    }
    
    // LDA Zero Page
    void LDA_ZP_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Byte address = cpu.fetchByte(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        Load_Execute(cpu, value, cpu.A);
    }

    // LDA Zero Page X
    void LDA_ZPX_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = addrZPX(cpu, mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        Load_Execute(cpu, value, cpu.A);
    }

    // LDA Absolute
    void LDA_ABS_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        Load_Execute(cpu, value, cpu.A);
    }

    // LDA Absolute,X
    void LDA_ABSX_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = addrABSX(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,address);
        Load_Execute(cpu, value, cpu.A);
    }

    // LDA Absolute,Y
    void LDA_ABSY_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = addrABSY(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,address);
        Load_Execute(cpu, value, cpu.A);
    }

    // LDA Indirect,X
    void LDA_INDX_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word targetAddress = addrINDX(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,targetAddress);

        Load_Execute(cpu, value, cpu.A);
    }

    //LDA Indirect,Y
    void LDA_INDY_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word targetAddress = addrINDY(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,targetAddress);

        Load_Execute(cpu, value, cpu.A);
    }

    /*
     * L
     * D
     * X
     */
    
    // LDX Immediate
    void LDX_IMM_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Byte value = cpu.fetchByte(mem, cycles);
        Load_Execute(cpu, value, cpu.X);
    }

    // LDX Zero Page
    void LDX_ZP_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Byte address = cpu.fetchByte(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        Load_Execute(cpu, value, cpu.X);
    }

    // LDX Zero Page,Y
    void LDX_ZPY_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = addrZPY(cpu, mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        Load_Execute(cpu, value, cpu.X);
    }

    // LDX Absolute
    void LDX_ABS_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        Load_Execute(cpu, value, cpu.X);
    }

    // LDX Absolute,Y
    void LDX_ABSY_func(CPU &cpu, const Memory &mem, int32 &cycles) {
        Word address = addrABSY(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,address);
        Load_Execute(cpu, value, cpu.X);
    }

    /*
     * L
     * D
     * Y
     */
    
    // LDY Immediate
    void LDY_IMM_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Byte value = cpu.fetchByte(mem, cycles);
        Load_Execute(cpu, value, cpu.Y);
    }

    // LDY Zero Page
    void LDY_ZP_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Byte address = cpu.fetchByte(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        Load_Execute(cpu, value, cpu.Y);
    }

    // LDY Zero Page,X
    void LDY_ZPX_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = addrZPX(cpu, mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        Load_Execute(cpu, value, cpu.Y);
    }

    // LDY Absolute
    void LDY_ABS_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = cpu.fetchWord(mem, cycles);
        Byte value = CPU::readByte(mem, cycles, address);
        Load_Execute(cpu, value, cpu.Y);
    }

    // LDY Absolute,X
    void LDY_ABSX_func(CPU& cpu, const Memory& mem, int32& cycles) {
        Word address = addrABSX(cpu,mem,cycles);
        Byte value = CPU::readByte(mem,cycles,address);
        Load_Execute(cpu, value, cpu.Y);
    }
}
