#include  "CPU.h"
#include "Instructions.h"

namespace Instructions {
    void IncDec(CPU& cpu, Bus& Bus, int32& cycles, Word address, bool inc=true) {
        Byte val = CPU::readByte(Bus, cycles, address);

        if (inc) val++;
        else val--;

        CPU::consumeCycle(cycles);
        cpu.setFlag(CPU::Z, (val == 0));
        cpu.setFlag(CPU::N, (val & 0x80) != 0);

        CPU::writeByte(Bus, cycles, address, val);
    }

    void DINC(CPU& cpu, Bus& Bus, int32& cycles, const AddrMode mode, bool inc) {
        Word address;
        switch (mode) {
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPX:  address = addrZPX(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            case AddrMode::ABSX: address = addrABSX(cpu, Bus, cycles,true); break;
            default: return;
        }
        IncDec(cpu, Bus, cycles, address, inc);
    }

    void DINX(CPU& cpu, int32& cycles, bool inc) {
        if (inc) cpu.X++;
        else cpu.X--;
        CPU::consumeCycle(cycles);

        cpu.setFlag(CPU::Z, (cpu.X == 0));
        cpu.setFlag(CPU::N, (cpu.X & 0x80) != 0);
    };

    void DINY(CPU& cpu, int32& cycles, bool inc) {
        if (inc) cpu.Y++;
        else cpu.Y--;
        CPU::consumeCycle(cycles);

        cpu.setFlag(CPU::Z, (cpu.Y == 0));
        cpu.setFlag(CPU::N, (cpu.Y & 0x80) != 0);
    };

}

