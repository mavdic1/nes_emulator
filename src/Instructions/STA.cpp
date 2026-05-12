#include "Instructions.h"

namespace Instructions {

    // Internal helper
    static void STA_Execute(Memory& mem, CPU& cpu, u32& cycles, Word address)
    {
        CPU::writeByte(mem,cycles,address,cpu.A);
    }

    void RegisterSTA() {
        // STA Zero Page
        table[STA_ZP] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Byte address = cpu.fetchByte(mem, cycles);
            STA_Execute(mem, cpu, cycles,address);
        };

        // STA Zero Page X
        table[STA_ZPX] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Byte address = addrZPX(cpu, mem, cycles);
            STA_Execute(mem, cpu, cycles,address);
        };

        // STA Absolute
        table[STA_ABS] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = cpu.fetchWord(mem, cycles);
            STA_Execute(mem, cpu, cycles,address);
        };

        // STA Absolute,X
        table[STA_ABSX] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrABSX(cpu,mem,cycles,true);
            STA_Execute(mem, cpu, cycles,address);
        };

        // STA Absolute,Y
        table[STA_ABSY] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrABSY(cpu,mem,cycles,true);
            STA_Execute(mem, cpu, cycles,address);
        };

        // STA Indirect,X
        table[STA_INDX] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrINDX(cpu,mem,cycles);
            STA_Execute(mem, cpu, cycles,address);
        };

        // STA Indirect,Y
        table[STA_INDY] = [](CPU& cpu, Memory& mem, u32& cycles) {
            Word address = addrINDY(cpu,mem,cycles,true);
            STA_Execute(mem, cpu, cycles,address);
        };
    }
}