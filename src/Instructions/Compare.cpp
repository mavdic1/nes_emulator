#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Internal helper for all comparisons
    static void Compare_Execute(CPU& cpu, const Bus& Bus, int32& cycles, Word address, Byte reg) {
        Byte val = CPU::readByte(Bus, cycles, address);

        // Carry is set if Register >= Bus
        cpu.setFlag(CPU::C, reg >= val);

        // Result of the internal subtraction
        Byte result = reg - val;
        cpu.setFlag(CPU::Z, result == 0);
        cpu.setFlag(CPU::N, (result & 0x80) != 0);
    }

    /*
     * CMP (Compare Accumulator)
     * Supports all 8 modes like LDA
     */
    void CMP(CPU& cpu, const Bus& Bus, int32& cycles, const AddrMode mode) {
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
        Compare_Execute(cpu, Bus, cycles, address, cpu.A);
    }

    /*
     * CPX (Compare X Register)
     * Only supports IMM, ZP, ABS
     */
    void CPX(CPU& cpu, const Bus& Bus, int32& cycles, const AddrMode mode) {
        Word address;
        switch (mode) {
            case AddrMode::IMM:  address = addrIMM(cpu); break;
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            default: return;
        }
        Compare_Execute(cpu, Bus, cycles, address, cpu.X);
    }

    /*
     * CPY (Compare Y Register)
     * Only supports IMM, ZP, ABS
     */
    void CPY(CPU& cpu, const Bus& Bus, int32& cycles, const AddrMode mode) {
        Word address;
        switch (mode) {
            case AddrMode::IMM:  address = addrIMM(cpu); break;
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            default: return;
        }
        Compare_Execute(cpu, Bus, cycles, address, cpu.Y);
    }
}