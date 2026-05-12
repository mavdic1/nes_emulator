#include "Instructions.h"

namespace Instructions {

    // Internal helper
    static void LDA_Execute(CPU& cpu, Byte value) {
        cpu.A = value;
        cpu.setFlag(CPU::Z, (cpu.A == 0));
        cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
    }

    void RegisterLDA() {
        // LDA Immediate
        table[LDA_IMM] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Byte value = cpu.fetchByte(mem, cycles);
            LDA_Execute(cpu, value);
        };

        // LDA Zero Page
        table[LDA_ZP] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Byte address = cpu.fetchByte(mem, cycles);
            Byte value = CPU::readByte(mem, cycles, address);
            LDA_Execute(cpu, value);
        };

        // LDA Zero Page X
        table[LDA_ZPX] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrZPX(cpu, mem, cycles);
            Byte value = CPU::readByte(mem, cycles, address);
            LDA_Execute(cpu, value);
        };

        // LDA Absolute
        table[LDA_ABS] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = cpu.fetchWord(mem, cycles);
            Byte value = CPU::readByte(mem, cycles, address);
            LDA_Execute(cpu, value);
        };

        // LDA Absolute,X
        table[LDA_ABSX] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrABSX(cpu,mem,cycles);
            Byte value = CPU::readByte(mem,cycles,address);
            LDA_Execute(cpu, value);
        };

        // LDA Absolute,Y
        table[LDA_ABSY] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrABSY(cpu,mem,cycles);
            Byte value = CPU::readByte(mem,cycles,address);
            LDA_Execute(cpu, value);
        };

        // LDA Indirect,X
        table[LDA_INDX] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word targetAddress = addrINDX(cpu,mem,cycles);
            Byte value = CPU::readByte(mem,cycles,targetAddress);

            LDA_Execute(cpu, value);
        };

        //LDA Indirect,Y
        table[LDA_INDY] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word targetAddress = addrINDY(cpu,mem,cycles);
            Byte value = CPU::readByte(mem,cycles,targetAddress);

            LDA_Execute(cpu, value);
        };
    }
}