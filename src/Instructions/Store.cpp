#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Internal helper
    static void Store_Execute(CPU& cpu, Bus& Bus, int32& cycles, Word address, const Byte& reg) {
        CPU::writeByte(Bus, cycles, address, reg);
    }

    void STA(CPU& cpu, Bus& Bus, int32& cycles, const AddrMode mode) {
        Word address;
        switch (mode) {
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPX:  address = addrZPX(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            case AddrMode::ABSX: address = addrABSX(cpu, Bus, cycles, true); break;
            case AddrMode::ABSY: address = addrABSY(cpu, Bus, cycles, true); break;
            case AddrMode::INDX: address = addrINDX(cpu, Bus, cycles); break;
            case AddrMode::INDY: address = addrINDY(cpu, Bus, cycles, true); break;
            default: return;
        }
        Store_Execute(cpu, Bus, cycles, address, cpu.A);
    }

    void STX(CPU& cpu, Bus& Bus, int32& cycles, const AddrMode mode) {
        Word address;
        switch (mode) {
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPY:  address = addrZPY(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            default: return;
        }
        Store_Execute(cpu, Bus, cycles, address, cpu.X);
    }

    void STY(CPU& cpu, Bus& Bus, int32& cycles, const AddrMode mode) {
        Word address;
        switch (mode) {
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPX:  address = addrZPX(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            default: return;
        }
        Store_Execute(cpu, Bus, cycles, address, cpu.Y);
    }
}
