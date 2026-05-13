#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Helper for Bus-based shifts (Read-Modify-Write)
    enum class ShiftType { ASL, LSR, ROL, ROR };

    static void Shift_Bus(CPU& cpu, Bus& Bus, int32& cycles, Word address, ShiftType type) {
        Byte val = CPU::readByte(Bus, cycles, address);
        CPU::consumeCycle(cycles);

        Byte oldCarry = (cpu.P & CPU::C) ? 1 : 0;
        
        if (type == ShiftType::ASL) {
            cpu.setFlag(CPU::C, (val & 0x80) != 0);
            val <<= 1;
        } 
        else if (type == ShiftType::LSR) {
            cpu.setFlag(CPU::C, (val & 0x01) != 0);
            val >>= 1;
        }
        else if (type == ShiftType::ROL) {
            bool willCarry = (val & 0x80) != 0;
            val = (val << 1) | oldCarry;
            cpu.setFlag(CPU::C, willCarry);
        }
        else {
            bool willCarry = (val & 0x01) != 0;
            val = (val >> 1) | (oldCarry << 7);
            cpu.setFlag(CPU::C, willCarry);
        }

        cpu.setFlag(CPU::Z, val == 0);
        cpu.setFlag(CPU::N, (val & 0x80) != 0);
        CPU::writeByte(Bus, cycles, address, val);
    }

    // Accumulator versions (much faster, no Bus write)
    void ASL_Acc(CPU& cpu, int32& cycles) {
        cpu.setFlag(CPU::C, (cpu.A & 0x80) != 0);
        cpu.A <<= 1;
        CPU::consumeCycle(cycles);
        cpu.setFlag(CPU::Z, cpu.A == 0);
        cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
    }

    void LSR_Acc(CPU& cpu, int32& cycles) {
        cpu.setFlag(CPU::C, (cpu.A & 0x01) != 0);
        cpu.A >>= 1;
        CPU::consumeCycle(cycles);
        cpu.setFlag(CPU::Z, cpu.A == 0);
        cpu.setFlag(CPU::N, false);
    }

    void ROL_Acc(CPU& cpu, int32& cycles) {
        Byte oldCarry = (cpu.P & CPU::C) ? 1 : 0;
        cpu.setFlag(CPU::C, (cpu.A & 0x80) != 0);
        cpu.A = (cpu.A << 1) | oldCarry;
        CPU::consumeCycle(cycles);
        cpu.setFlag(CPU::Z, cpu.A == 0);
        cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
    }

    void ROR_Acc(CPU& cpu, int32& cycles) {
        Byte oldCarry = (cpu.P & CPU::C) ? 1 : 0;
        cpu.setFlag(CPU::C, (cpu.A & 0x01) != 0);
        cpu.A = (cpu.A >> 1) | (oldCarry << 7);
        CPU::consumeCycle(cycles);
        cpu.setFlag(CPU::Z, cpu.A == 0);
        cpu.setFlag(CPU::N, (cpu.A & 0x80) != 0);
    }

    // Generic Bus Shift interfaces
    void ASL(CPU& cpu, Bus& Bus, int32& cycles, AddrMode mode) {
        Word address;
        switch(mode) {
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPX:  address = addrZPX(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            case AddrMode::ABSX: address = addrABSX(cpu, Bus, cycles, true); break;
            default: return;
        }
        Shift_Bus(cpu, Bus, cycles, address, ShiftType::ASL);
    }

    void LSR(CPU& cpu, Bus& Bus, int32& cycles, AddrMode mode) {
        Word address;
        switch(mode) {
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPX:  address = addrZPX(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            case AddrMode::ABSX: address = addrABSX(cpu, Bus, cycles, true); break;
            default: return;
        }
        Shift_Bus(cpu, Bus, cycles, address, ShiftType::LSR);
    }

    void ROL(CPU& cpu, Bus& Bus, int32& cycles, AddrMode mode) {
        Word address;
        switch(mode) {
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPX:  address = addrZPX(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            case AddrMode::ABSX: address = addrABSX(cpu, Bus, cycles, true); break;
            default: return;
        }
        Shift_Bus(cpu, Bus, cycles, address, ShiftType::ROL);
    }

    void ROR(CPU& cpu, Bus& Bus, int32& cycles, AddrMode mode) {
        Word address;
        switch(mode) {
            case AddrMode::ZP:   address = addrZP(cpu, Bus, cycles); break;
            case AddrMode::ZPX:  address = addrZPX(cpu, Bus, cycles); break;
            case AddrMode::ABS:  address = addrABS(cpu, Bus, cycles); break;
            case AddrMode::ABSX: address = addrABSX(cpu, Bus, cycles, true); break;
            default: return;
        }
        Shift_Bus(cpu, Bus, cycles, address, ShiftType::ROR);
    }
}