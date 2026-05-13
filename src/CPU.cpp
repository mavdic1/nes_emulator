#include "CPU.h"
#include "Instructions/Instructions.h"
#include <iostream>

void CPU::reset(Memory& mem) //Reset function
{
    //mem.Initialize(); //Initialize memory

    const Word lo = mem.Read(0xFFFC); //Reset vector low
    const Word hi = mem.Read(0xFFFD); //Reset vector high
    PC = (hi << 8) | lo; //Set Program Counter to address from memory based on reset vector

    S = 0xFD; // Set the stack to NES standard location

    A = X = Y = 0; //Registers reset to 0 for safety

    P = I | U; // Ensure Unused bit is 1 and Interrupts are disabled on start

}

void CPU::consumeCycle(int32& cycles)
{
    if (cycles > 0) cycles--;
}

Byte CPU::fetchByte(const Memory& mem, int32& cycles) //Fetches byte from memory at current PC
{
    Byte Data = mem.Read(PC);
    PC += 1;
    if (cycles > 0) cycles--;
    return Data;
}

Byte CPU::readByte(const Memory& mem, int32& cycles, Word address) //Fetches byte from memory at current PC
{
    Byte Data = mem.Read(address);
    if (cycles > 0) cycles--;
    return Data;
}

void CPU::writeByte(Memory& mem, int32& cycles, Word address, Byte value)
{
    mem.Write(address,value);
    consumeCycle(cycles);
}

Word CPU::fetchWord(const Memory& mem, int32& cycles) //Fetches word from memory
{
    Word lo = fetchByte(mem, cycles);
    Word hi = fetchByte(mem, cycles);
    Word value = hi << 8 | lo;
    return value;
}

Word CPU::readWord(const Memory& mem, int32& cycles, Word address) //Fetches word at specific address
{
    Word lo = readByte(mem, cycles,address);
    Word hi = readByte(mem, cycles,address+1);
    Word value = hi << 8 | lo;
    return value;
}

Word CPU::readWordPageWrap(const Memory& mem, int32& cycles, Word address)
{
    Word lo = readByte(mem, cycles, address);
    Word hiAddress = (address & 0xFF00) | ((address + 1) & 0x00FF);
    Word hi = readByte(mem, cycles, hiAddress);

    return (hi << 8) | lo;
}

void CPU::execute(Memory& mem, int32 cycles) //Execute
{
    while (cycles > 0)
    {
        //Simple debugging logger
        printf("PC: %04X | Op: %02X | A: %02X X: %02X Y: %02X S: %02X\n", PC, mem.Read(PC), A, X, Y, S);

        switch (const Byte opcode = fetchByte(mem, cycles)) {
            //LDA
            case Instructions::LDA_IMM: Instructions::LDA_IMM_func(*this,mem, cycles); break;
            case Instructions::LDA_ZP: Instructions::LDA_ZP_func(*this,mem, cycles); break;
            case Instructions::LDA_ZPX: Instructions::LDA_ZPX_func(*this,mem, cycles); break;
            case Instructions::LDA_ABS: Instructions::LDA_ABS_func(*this,mem, cycles); break;
            case Instructions::LDA_ABSX: Instructions::LDA_ABSX_func(*this,mem, cycles); break;
            case Instructions::LDA_ABSY: Instructions::LDA_ABSY_func(*this,mem, cycles); break;
            case Instructions::LDA_INDX: Instructions::LDA_INDX_func(*this,mem, cycles); break;
            case Instructions::LDA_INDY: Instructions::LDA_INDY_func(*this,mem, cycles); break;

            //LDX
            case Instructions::LDX_IMM: Instructions::LDX_IMM_func(*this,mem, cycles); break;
            case Instructions::LDX_ZP: Instructions::LDX_ZP_func(*this,mem, cycles); break;
            case Instructions::LDX_ZPY: Instructions::LDX_ZPY_func(*this,mem, cycles); break;
            case Instructions::LDX_ABS: Instructions::LDX_ABS_func(*this,mem, cycles); break;
            case Instructions::LDX_ABSY: Instructions::LDX_ABSY_func(*this,mem, cycles); break;
                
            //LDY
            case Instructions::LDY_IMM: Instructions::LDY_IMM_func(*this,mem, cycles); break;
            case Instructions::LDY_ZP: Instructions::LDY_ZP_func(*this,mem, cycles); break;
            case Instructions::LDY_ZPX: Instructions::LDY_ZPX_func(*this,mem, cycles); break;
            case Instructions::LDY_ABS: Instructions::LDY_ABS_func(*this,mem, cycles); break;
            case Instructions::LDY_ABSX: Instructions::LDY_ABSX_func(*this,mem, cycles); break;
                
            //STA
            case Instructions::STA_ZP: Instructions::STA_ZP_func(*this,mem, cycles); break;
            case Instructions::STA_ZPX: Instructions::STA_ZPX_func(*this,mem, cycles); break;
            case Instructions::STA_ABS: Instructions::STA_ABS_func(*this,mem, cycles); break;
            case Instructions::STA_ABSX: Instructions::STA_ABSX_func(*this,mem, cycles); break;
            case Instructions::STA_ABSY: Instructions::STA_ABSY_func(*this,mem, cycles); break;
            case Instructions::STA_INDX: Instructions::STA_INDX_func(*this,mem, cycles); break;
            case Instructions::STA_INDY: Instructions::STA_INDY_func(*this,mem, cycles); break;
                
            //STX
            case Instructions::STX_ZP: Instructions::STX_ZP_func(*this,mem, cycles); break;
            case Instructions::STX_ZPY: Instructions::STX_ZPY_func(*this,mem, cycles); break;
            case Instructions::STX_ABS: Instructions::STX_ABS_func(*this,mem, cycles); break;
                
            //STY
            case Instructions::STY_ZP: Instructions::STY_ZP_func(*this,mem, cycles); break;
            case Instructions::STY_ZPX: Instructions::STY_ZPX_func(*this,mem, cycles); break;
            case Instructions::STY_ABS: Instructions::STY_ABS_func(*this,mem, cycles); break;
                
            //Transfer
            case Instructions::TAX: Instructions::TAX_func(*this, cycles); break;
            case Instructions::TAY: Instructions::TAY_func(*this, cycles); break;
            case Instructions::TSX: Instructions::TSX_func(*this, cycles); break;
            case Instructions::TXA: Instructions::TXA_func(*this, cycles); break;
            case Instructions::TXS: Instructions::TXS_func(*this, cycles); break;
            case Instructions::TYA: Instructions::TYA_func(*this, cycles); break;

            //Stack
            case Instructions::PLA: Instructions::PLA_func(*this, mem, cycles); break;
            case Instructions::PLP: Instructions::PLP_func(*this, mem, cycles); break;
            case Instructions::PHA: Instructions::PHA_func(*this, mem, cycles); break;
            case Instructions::PHP: Instructions::PHP_func(*this, mem, cycles); break;

            default:
                std::cerr << "Unknown opcode: " << std::hex << + opcode
                          << " at PC: " << (PC - 1) << std::dec << std::endl;
                break;
        }
    }
}