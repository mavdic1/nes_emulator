#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Internal helper for ADC (Add with Carry)
    static void ADC_Execute(CPU& cpu, int32& cycles, Byte val) {
        const Byte carry = (cpu.P & CPU::C) ? 1 : 0;
        const Word result = cpu.A + val + carry;

        cpu.setFlag(CPU::C, result > 0xFF);

        cpu.setFlag(CPU::V, (~(cpu.A ^ val) & (cpu.A ^ static_cast<Byte>(result)) & 0x80));

        cpu.A = static_cast<Byte>(result & 0xFF);

        cpu.setFlag(CPU::Z, cpu.A == 0);
        cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
    }

    void ADC(CPU& cpu, const Bus& Bus, int32& cycles, AddrMode mode) {
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
        ADC_Execute(cpu, cycles, CPU::readByte(Bus, cycles, address));
    }

    void SBC(CPU& cpu, const Bus& Bus, int32& cycles, AddrMode mode) {
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
        ADC_Execute(cpu, cycles, ~CPU::readByte(Bus, cycles, address));
    }
}