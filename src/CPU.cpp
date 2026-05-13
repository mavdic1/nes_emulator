#include "CPU.h"
#include "Instructions/Instructions.h"
#include <iostream>

void CPU::reset(Bus& Bus) //Reset function
{
    //Bus.Initialize(); //Initialize Bus

    const Word lo = Bus.Read(0xFFFC); //Reset vector low
    const Word hi = Bus.Read(0xFFFD); //Reset vector high
    PC = (hi << 8) | lo; //Set Program Counter to address from Bus based on reset vector

    S = 0xFD; // Set the stack to NES standard location

    A = X = Y = 0; //Registers reset to 0 for safety

    P = I | U; // Ensure Unused bit is 1 and Interrupts are disabled on start

}

void CPU::consumeCycle(int32& cycles)
{
    cycles--;
}

Byte CPU::fetchByte(const Bus& Bus, int32& cycles) //Fetches byte from Bus at current PC
{
    Byte Data = Bus.Read(PC);
    PC += 1;
    cycles--;
    return Data;
}

Byte CPU::readByte(const Bus& Bus, int32& cycles, Word address) //Fetches byte from Bus at current PC
{
    Byte Data = Bus.Read(address);
    cycles--;
    return Data;
}

void CPU::writeByte(Bus& Bus, int32& cycles, Word address, Byte value)
{
    Bus.Write(address,value);
    consumeCycle(cycles);
}

Word CPU::fetchWord(const Bus& Bus, int32& cycles) //Fetches word from Bus
{
    Word lo = fetchByte(Bus, cycles);
    Word hi = fetchByte(Bus, cycles);
    Word value = hi << 8 | lo;
    return value;
}

Word CPU::readWord(const Bus& Bus, int32& cycles, Word address) //Fetches word at specific address
{
    Word lo = readByte(Bus, cycles,address);
    Word hi = readByte(Bus, cycles,address+1);
    Word value = hi << 8 | lo;
    return value;
}

Word CPU::readWordPageWrap(const Bus& Bus, int32& cycles, Word address)
{
    Word lo = readByte(Bus, cycles, address);
    Word hiAddress = (address & 0xFF00) | ((address + 1) & 0x00FF);
    Word hi = readByte(Bus, cycles, hiAddress);

    return (hi << 8) | lo;
}

void CPU::execute(Bus& Bus, int32 cycles) //Execute
{
    while (cycles > 0)
    {
        //Simple debugging logger
        printf("PC: %04X | Op: %02X | A: %02X X: %02X Y: %02X S: %02X\n", PC, Bus.Read(PC), A, X, Y, S);

        switch (const Byte opcode = fetchByte(Bus, cycles)) {
            //LDA
            case Instructions::LDA_IMM: Instructions::LDA(*this,Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::LDA_ZP: Instructions::LDA(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::LDA_ZPX: Instructions::LDA(*this,Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::LDA_ABS: Instructions::LDA(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::LDA_ABSX: Instructions::LDA(*this,Bus, cycles, Instructions::AddrMode::ABSX); break;
            case Instructions::LDA_ABSY: Instructions::LDA(*this,Bus, cycles, Instructions::AddrMode::ABSY); break;
            case Instructions::LDA_INDX: Instructions::LDA(*this,Bus, cycles, Instructions::AddrMode::INDX); break;
            case Instructions::LDA_INDY: Instructions::LDA(*this,Bus, cycles, Instructions::AddrMode::INDY); break;

            //LDX
            case Instructions::LDX_IMM: Instructions::LDX(*this,Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::LDX_ZP: Instructions::LDX(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::LDX_ZPY: Instructions::LDX(*this,Bus, cycles, Instructions::AddrMode::ZPY); break;
            case Instructions::LDX_ABS: Instructions::LDX(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::LDX_ABSY: Instructions::LDX(*this,Bus, cycles, Instructions::AddrMode::ABSY); break;
                
            //LDY
            case Instructions::LDY_IMM: Instructions::LDY(*this,Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::LDY_ZP: Instructions::LDY(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::LDY_ZPX: Instructions::LDY(*this,Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::LDY_ABS: Instructions::LDY(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::LDY_ABSX: Instructions::LDY(*this,Bus, cycles, Instructions::AddrMode::ABSX); break;
                
            //STA
            case Instructions::STA_ZP: Instructions::STA(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::STA_ZPX: Instructions::STA(*this,Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::STA_ABS: Instructions::STA(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::STA_ABSX: Instructions::STA(*this,Bus, cycles, Instructions::AddrMode::ABSX); break;
            case Instructions::STA_ABSY: Instructions::STA(*this,Bus, cycles, Instructions::AddrMode::ABSY); break;
            case Instructions::STA_INDX: Instructions::STA(*this,Bus, cycles, Instructions::AddrMode::INDX); break;
            case Instructions::STA_INDY: Instructions::STA(*this,Bus, cycles, Instructions::AddrMode::INDY); break;
                
            //STX
            case Instructions::STX_ZP: Instructions::STX(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::STX_ZPY: Instructions::STX(*this,Bus, cycles, Instructions::AddrMode::ZPY); break;
            case Instructions::STX_ABS: Instructions::STX(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
                
            //STY
            case Instructions::STY_ZP: Instructions::STY(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::STY_ZPX: Instructions::STY(*this,Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::STY_ABS: Instructions::STY(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
                
            //Transfer
            case Instructions::TAX: Instructions::TAX_func(*this, cycles); break;
            case Instructions::TAY: Instructions::TAY_func(*this, cycles); break;
            case Instructions::TSX: Instructions::TSX_func(*this, cycles); break;
            case Instructions::TXA: Instructions::TXA_func(*this, cycles); break;
            case Instructions::TXS: Instructions::TXS_func(*this, cycles); break;
            case Instructions::TYA: Instructions::TYA_func(*this, cycles); break;

            //Stack
            case Instructions::PLA: Instructions::PLA_func(*this, Bus, cycles); break;
            case Instructions::PLP: Instructions::PLP_func(*this, Bus, cycles); break;
            case Instructions::PHA: Instructions::PHA_func(*this, Bus, cycles); break;
            case Instructions::PHP: Instructions::PHP_func(*this, Bus, cycles); break;
                
            //AND
            case Instructions::AND_IMM: Instructions::AND(*this,Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::AND_ZP: Instructions::AND(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::AND_ZPX: Instructions::AND(*this,Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::AND_ABS: Instructions::AND(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::AND_ABSX: Instructions::AND(*this,Bus, cycles, Instructions::AddrMode::ABSX); break;
            case Instructions::AND_ABSY: Instructions::AND(*this,Bus, cycles, Instructions::AddrMode::ABSY); break;
            case Instructions::AND_INDX: Instructions::AND(*this,Bus, cycles, Instructions::AddrMode::INDX); break;
            case Instructions::AND_INDY: Instructions::AND(*this,Bus, cycles, Instructions::AddrMode::INDY); break;
                
            //EOR
            case Instructions::EOR_IMM: Instructions::EOR(*this,Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::EOR_ZP: Instructions::EOR(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::EOR_ZPX: Instructions::EOR(*this,Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::EOR_ABS: Instructions::EOR(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::EOR_ABSX: Instructions::EOR(*this,Bus, cycles, Instructions::AddrMode::ABSX); break;
            case Instructions::EOR_ABSY: Instructions::EOR(*this,Bus, cycles, Instructions::AddrMode::ABSY); break;
            case Instructions::EOR_INDX: Instructions::EOR(*this,Bus, cycles, Instructions::AddrMode::INDX); break;
            case Instructions::EOR_INDY: Instructions::EOR(*this,Bus, cycles, Instructions::AddrMode::INDY); break;
                
            //ORA
            case Instructions::ORA_IMM: Instructions::ORA(*this,Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::ORA_ZP: Instructions::ORA(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::ORA_ZPX: Instructions::ORA(*this,Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::ORA_ABS: Instructions::ORA(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::ORA_ABSX: Instructions::ORA(*this,Bus, cycles, Instructions::AddrMode::ABSX); break;
            case Instructions::ORA_ABSY: Instructions::ORA(*this,Bus, cycles, Instructions::AddrMode::ABSY); break;
            case Instructions::ORA_INDX: Instructions::ORA(*this,Bus, cycles, Instructions::AddrMode::INDX); break;
            case Instructions::ORA_INDY: Instructions::ORA(*this,Bus, cycles, Instructions::AddrMode::INDY); break;
                
            //CMP
            case Instructions::CMP_IMM: Instructions::CMP(*this,Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::CMP_ZP: Instructions::CMP(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::CMP_ZPX: Instructions::CMP(*this,Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::CMP_ABS: Instructions::CMP(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::CMP_ABSX: Instructions::CMP(*this,Bus, cycles, Instructions::AddrMode::ABSX); break;
            case Instructions::CMP_ABSY: Instructions::CMP(*this,Bus, cycles, Instructions::AddrMode::ABSY); break;
            case Instructions::CMP_INDX: Instructions::CMP(*this,Bus, cycles, Instructions::AddrMode::INDX); break;
            case Instructions::CMP_INDY: Instructions::CMP(*this,Bus, cycles, Instructions::AddrMode::INDY); break;

            //CPX
            case Instructions::CPX_IMM: Instructions::CPX(*this,Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::CPX_ZP: Instructions::CPX(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::CPX_ABS: Instructions::CPX(*this,Bus, cycles, Instructions::AddrMode::ABS); break;

            //CPY
            case Instructions::CPY_IMM: Instructions::CPY(*this,Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::CPY_ZP: Instructions::CPY(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::CPY_ABS: Instructions::CPY(*this,Bus, cycles, Instructions::AddrMode::ABS); break;

            //JMP
            case Instructions::JMP_ABS: Instructions::JMP(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::JMP_IND: Instructions::JMP(*this,Bus, cycles, Instructions::AddrMode::IND); break;

            //JSR
            case Instructions::JSR_ABS: Instructions::JSR(*this,Bus, cycles); break;

            //RTS
            case Instructions::RTS: Instructions::RTS_func(*this, Bus, cycles); break;

            //Branch
            case Instructions::BCC: Instructions::Branch(*this, Bus, cycles, !(P & C)); break;
            case Instructions::BCS: Instructions::Branch(*this, Bus, cycles, (P & C)); break;
            case Instructions::BEQ: Instructions::Branch(*this, Bus, cycles, (P & Z)); break;
            case Instructions::BMI: Instructions::Branch(*this, Bus, cycles, (P & N)); break;
            case Instructions::BNE: Instructions::Branch(*this, Bus, cycles, !(P & Z)); break;
            case Instructions::BPL: Instructions::Branch(*this, Bus, cycles, !(P & N)); break;
            case Instructions::BVC: Instructions::Branch(*this, Bus, cycles, !(P & V)); break;
            case Instructions::BVS: Instructions::Branch(*this, Bus, cycles, (P & V)); break;

            //Increment / Decrement
            case Instructions::INC_ZP: Instructions::DINC(*this,Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::INC_ZPX: Instructions::DINC(*this,Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::INC_ABS: Instructions::DINC(*this,Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::INC_ABSX: Instructions::DINC(*this,Bus, cycles, Instructions::AddrMode::ABSX); break;

            case Instructions::DEC_ZP: Instructions::DINC(*this,Bus, cycles, Instructions::AddrMode::ZP,false); break;
            case Instructions::DEC_ZPX: Instructions::DINC(*this,Bus, cycles, Instructions::AddrMode::ZPX,false); break;
            case Instructions::DEC_ABS: Instructions::DINC(*this,Bus, cycles, Instructions::AddrMode::ABS,false); break;
            case Instructions::DEC_ABSX: Instructions::DINC(*this,Bus, cycles, Instructions::AddrMode::ABSX,false); break;

            case Instructions::INX: Instructions::DINX(*this, cycles); break;
            case Instructions::INY: Instructions::DINY(*this, cycles); break;

            case Instructions::DEX: Instructions::DINX(*this, cycles,false); break;
            case Instructions::DEY: Instructions::DINY(*this, cycles,false); break;

            //Status Flags
            case Instructions::CLC: Instructions::CLC_func(*this, cycles); break;
            case Instructions::SEC: Instructions::SEC_func(*this, cycles); break;

            case Instructions::CLD: Instructions::CLD_func(*this, cycles); break;
            case Instructions::SED: Instructions::SED_func(*this, cycles); break;

            case Instructions::CLI: Instructions::CLI_func(*this, cycles); break;
            case Instructions::SEI: Instructions::SEI_func(*this, cycles); break;

            case Instructions::CLV: Instructions::CLV_func(*this, cycles); break;

            // System
            case Instructions::NOP: Instructions::NOP_func(*this, cycles); break;
            case Instructions::BIT_ZP: Instructions::BIT(*this, Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::BIT_ABS: Instructions::BIT(*this, Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::BRK: Instructions::BRK_func(*this, Bus, cycles); break;
            case Instructions::RTI: Instructions::RTI_func(*this, Bus, cycles); break;

            // ADC - Add with Carry
            case Instructions::ADC_IMM:  Instructions::ADC(*this, Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::ADC_ZP:   Instructions::ADC(*this, Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::ADC_ZPX:  Instructions::ADC(*this, Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::ADC_ABS:  Instructions::ADC(*this, Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::ADC_ABSX: Instructions::ADC(*this, Bus, cycles, Instructions::AddrMode::ABSX); break;
            case Instructions::ADC_ABSY: Instructions::ADC(*this, Bus, cycles, Instructions::AddrMode::ABSY); break;
            case Instructions::ADC_INDX: Instructions::ADC(*this, Bus, cycles, Instructions::AddrMode::INDX); break;
            case Instructions::ADC_INDY: Instructions::ADC(*this, Bus, cycles, Instructions::AddrMode::INDY); break;

            // SBC - Subtract with Carry
            case Instructions::SBC_IMM:  Instructions::SBC(*this, Bus, cycles, Instructions::AddrMode::IMM); break;
            case Instructions::SBC_ZP:   Instructions::SBC(*this, Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::SBC_ZPX:  Instructions::SBC(*this, Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::SBC_ABS:  Instructions::SBC(*this, Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::SBC_ABSX: Instructions::SBC(*this, Bus, cycles, Instructions::AddrMode::ABSX); break;
            case Instructions::SBC_ABSY: Instructions::SBC(*this, Bus, cycles, Instructions::AddrMode::ABSY); break;
            case Instructions::SBC_INDX: Instructions::SBC(*this, Bus, cycles, Instructions::AddrMode::INDX); break;
            case Instructions::SBC_INDY: Instructions::SBC(*this, Bus, cycles, Instructions::AddrMode::INDY); break;

            // ASL - Arithmetic Shift Left
            case Instructions::ASL_ACC:  Instructions::ASL_Acc(*this, cycles); break;
            case Instructions::ASL_ZP:   Instructions::ASL(*this, Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::ASL_ZPX:  Instructions::ASL(*this, Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::ASL_ABS:  Instructions::ASL(*this, Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::ASL_ABSX: Instructions::ASL(*this, Bus, cycles, Instructions::AddrMode::ABSX); break;

            // LSR - Logical Shift Right
            case Instructions::LSR_ACC:  Instructions::LSR_Acc(*this, cycles); break;
            case Instructions::LSR_ZP:   Instructions::LSR(*this, Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::LSR_ZPX:  Instructions::LSR(*this, Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::LSR_ABS:  Instructions::LSR(*this, Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::LSR_ABSX: Instructions::LSR(*this, Bus, cycles, Instructions::AddrMode::ABSX); break;

            // ROL - Rotate Left
            case Instructions::ROL_ACC:  Instructions::ROL_Acc(*this, cycles); break;
            case Instructions::ROL_ZP:   Instructions::ROL(*this, Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::ROL_ZPX:  Instructions::ROL(*this, Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::ROL_ABS:  Instructions::ROL(*this, Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::ROL_ABSX: Instructions::ROL(*this, Bus, cycles, Instructions::AddrMode::ABSX); break;

            // ROR - Rotate Right
            case Instructions::ROR_ACC:  Instructions::ROR_Acc(*this, cycles); break;
            case Instructions::ROR_ZP:   Instructions::ROR(*this, Bus, cycles, Instructions::AddrMode::ZP); break;
            case Instructions::ROR_ZPX:  Instructions::ROR(*this, Bus, cycles, Instructions::AddrMode::ZPX); break;
            case Instructions::ROR_ABS:  Instructions::ROR(*this, Bus, cycles, Instructions::AddrMode::ABS); break;
            case Instructions::ROR_ABSX: Instructions::ROR(*this, Bus, cycles, Instructions::AddrMode::ABSX); break;

            default:
                std::cerr << "Unknown opcode: " << std::hex << + opcode
                          << " at PC: " << (PC - 1) << std::dec << std::endl;
                break;
        }
    }
}