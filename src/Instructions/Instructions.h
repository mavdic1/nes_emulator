#pragma once
#include "../../include/Types.h"

/*
 * IMM - Immediate
 * ZP - Zero Page
 * ZPX - Zero Page,X
 * ABS - Absolute
 * ABSX - Absolute,X
 * ABSY - Absolute,Y
 * INDX - (Indirect,X)
 * INDY - (Indirect),Y
 */

//Opcodes contained in ./include/Types.h

struct CPU;    // Forward declaration
struct Bus; // Forward declaration

namespace Instructions {
    //Helper functions defined in Instructions.cpp
    //Addressing modes
    enum class AddrMode {
        IMM, ZP, ZPX, ZPY, ABS, ABSX, ABSY, IND, INDX, INDY
    };

    Word addrIMM(CPU& cpu);
    Word addrZP(CPU& cpu, const Bus& bus, int32& cycles);
    Word addrZPX( CPU& cpu, const Bus& bus, int32& cycles);
    Word addrZPY(CPU& cpu, const Bus& bus, int32& cycles);

    Word addrABS(CPU& cpu, const Bus& bus, int32& cycles);
    Word addrABSX( CPU& cpu, const Bus& bus, int32& cycles, bool alwaysPenalty = false);
    Word addrABSY(CPU& cpu, const Bus& bus, int32& cycles, bool alwaysPenalty = false);

    Word addrIND(CPU& cpu, const Bus& bus, int32& cycles);
    Word addrINDX(CPU& cpu, const Bus& bus, int32& cycles);
    Word addrINDY(CPU& cpu, const Bus& bus, int32& cycles, bool alwaysPenalty = false);

    //Load functions
    void LDA(CPU& cpu, const Bus& bus, int32& cycles, AddrMode mode);
    void LDX(CPU& cpu, const Bus& bus, int32& cycles, AddrMode mode);
    void LDY(CPU& cpu, const Bus& bus, int32& cycles, AddrMode mode);

    //Store functions
    void STA(CPU& cpu, Bus& bus, int32& cycles, AddrMode mode);
    void STX(CPU& cpu, Bus& bus, int32& cycles, AddrMode mode);
    void STY(CPU& cpu, Bus& bus, int32& cycles, AddrMode mode);

    //Transfer functions
    void TAX_func(CPU& cpu, int32& cycles);
    void TAY_func(CPU& cpu, int32& cycles);
    void TSX_func(CPU& cpu, int32& cycles);
    void TXA_func(CPU& cpu, int32& cycles);
    void TXS_func(CPU& cpu, int32& cycles);
    void TYA_func(CPU& cpu, int32& cycles);

    //Stack functions
    void PHA_func(CPU& cpu, Bus& bus, int32& cycles);
    void PLA_func(CPU& cpu, Bus& bus, int32& cycles);
    void PHP_func(CPU& cpu, Bus& bus, int32& cycles);
    void PLP_func(CPU& cpu, Bus& bus, int32& cycles);

    //Logic
    void AND(CPU& cpu, const Bus& bus, int32& cycles,AddrMode mode);
    void EOR(CPU& cpu, const Bus& bus, int32& cycles,AddrMode mode);
    void ORA(CPU& cpu, const Bus& bus, int32& cycles,AddrMode mode);

    //Compare
    void CMP(CPU& cpu, const Bus& bus, int32& cycles,AddrMode mode);
    void CPX(CPU& cpu, const Bus& bus, int32& cycles,AddrMode mode);
    void CPY(CPU& cpu, const Bus& bus, int32& cycles,AddrMode mode);

    //Jump
    void JMP(CPU& cpu, const Bus& bus, int32& cycles,AddrMode mode);
    void JSR(CPU& cpu, Bus& bus, int32& cycles);
    void RTS_func(CPU& cpu, Bus& bus, int32& cycles);

    //Branch
    void Branch(CPU& cpu, const Bus& bus, int32& cycles, bool condition);

    //Incrementing / Decrementing
    void DINC(CPU& cpu, Bus& bus, int32& cycles, AddrMode mode, bool inc=true);
    void DINX(CPU& cpu, int32& cycles, bool inc=true);
    void DINY(CPU& cpu, int32& cycles, bool inc=true);

    //Status Flag
    void CLC_func(CPU& cpu, int32& cycles);
    void SEC_func(CPU& cpu, int32& cycles);

    void CLD_func(CPU& cpu, int32& cycles);
    void SED_func(CPU& cpu, int32& cycles);

    void CLI_func(CPU& cpu, int32& cycles);
    void SEI_func(CPU& cpu, int32& cycles);

    void CLV_func(CPU& cpu, int32& cycles);

    //System
    void NOP_func(CPU& cpu, int32& cycles);
    void BIT(CPU& cpu, const Bus& bus, int32& cycles, AddrMode mode);
    void BRK_func(CPU& cpu, Bus& bus, int32& cycles);
    void RTI_func(CPU& cpu, Bus& bus, int32& cycles);

    // Arithmetic
    void ADC(CPU& cpu, const Bus& bus, int32& cycles, AddrMode mode);
    void SBC(CPU& cpu, const Bus& bus, int32& cycles, AddrMode mode);

    // Bitwise
    void ASL_Acc(CPU& cpu, int32& cycles);
    void ASL(CPU& cpu, Bus& bus, int32& cycles, AddrMode mode);
    void LSR_Acc(CPU& cpu, int32& cycles);
    void LSR(CPU& cpu, Bus& bus, int32& cycles, AddrMode mode);
    void ROL_Acc(CPU& cpu, int32& cycles);
    void ROL(CPU& cpu, Bus& bus, int32& cycles, AddrMode mode);
    void ROR_Acc(CPU& cpu, int32& cycles);
    void ROR(CPU& cpu, Bus& bus, int32& cycles, AddrMode mode);

}