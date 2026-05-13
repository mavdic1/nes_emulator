#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {

    // Helper for AND, ORA, EOR
    static void AND_Execute(CPU& cpu, const Bus& Bus, int32& cycles, Word address) {
        cpu.A &= CPU::readByte(Bus, cycles, address);
        cpu.setFlag(CPU::Z, (cpu.A == 0));
        cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
    }

    static void EOR_Execute(CPU& cpu, const Bus& Bus, int32& cycles, Word address) {
        cpu.A ^= CPU::readByte(Bus, cycles, address);
        cpu.setFlag(CPU::Z, (cpu.A == 0));
        cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
    }

    static void ORA_Execute(CPU& cpu, const Bus& Bus, int32& cycles, Word address) {
        cpu.A |= CPU::readByte(Bus, cycles, address);
        cpu.setFlag(CPU::Z, (cpu.A == 0));
        cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
    }

    void AND(CPU& cpu, const Bus& Bus, int32& cycles, const AddrMode mode) {
        Word address;
        switch (mode) {
            case AddrMode::IMM:  address = addrIMM(cpu); break;
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPX:  address = addrZPX(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            case AddrMode::ABSX: address = addrABSX(cpu, Bus, cycles); break;
            case AddrMode::ABSY: address = addrABSY(cpu, Bus, cycles); break;
            case AddrMode::INDX: address = addrINDX(cpu, Bus, cycles); break;
            case AddrMode::INDY: address = addrINDY(cpu, Bus, cycles); break;
            default: return;
        }
        AND_Execute(cpu, Bus, cycles, address);
    }

    void EOR(CPU& cpu, const Bus& Bus, int32& cycles, const AddrMode mode) {
        Word address;
        switch (mode) {
            case AddrMode::IMM:  address = addrIMM(cpu); break;
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPX:  address = addrZPX(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            case AddrMode::ABSX: address = addrABSX(cpu, Bus, cycles); break;
            case AddrMode::ABSY: address = addrABSY(cpu, Bus, cycles); break;
            case AddrMode::INDX: address = addrINDX(cpu, Bus, cycles); break;
            case AddrMode::INDY: address = addrINDY(cpu, Bus, cycles); break;
            default: return;
        }
        EOR_Execute(cpu, Bus, cycles, address);
    }

    void ORA(CPU& cpu, const Bus& Bus, int32& cycles, const AddrMode mode) {
        Word address;
        switch (mode) {
            case AddrMode::IMM:  address = addrIMM(cpu); break;
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPX:  address = addrZPX(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            case AddrMode::ABSX: address = addrABSX(cpu, Bus, cycles); break;
            case AddrMode::ABSY: address = addrABSY(cpu, Bus, cycles); break;
            case AddrMode::INDX: address = addrINDX(cpu, Bus, cycles); break;
            case AddrMode::INDY: address = addrINDY(cpu, Bus, cycles); break;
            default: return;
        }
        ORA_Execute(cpu, Bus, cycles, address);
    }
}
