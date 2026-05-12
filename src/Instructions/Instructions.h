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
struct Memory; // Forward declaration

namespace Instructions {
    //Helper functions defined in Instructions.cpp
    Word addrZPX( CPU& cpu, const Memory& mem, int32& cycles);
    Word addrZPY(CPU& cpu, const Memory& mem, int32& cycles);
    Word addrABSX( CPU& cpu, const Memory& mem, int32& cycles, bool alwaysPenalty = false);
    Word addrABSY(CPU& cpu, const Memory& mem, int32& cycles, bool alwaysPenalty = false);
    Word addrINDX(CPU& cpu, const Memory& mem, int32& cycles);
    Word addrINDY(CPU& cpu, const Memory& mem, int32& cycles, bool alwaysPenalty = false);

    //LDA functions
    void LDA_IMM_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDA_ZP_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDA_ZPX_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDA_ABS_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDA_ABSX_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDA_ABSY_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDA_INDX_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDA_INDY_func(CPU& cpu, const Memory& mem, int32& cycles);

    //LDX functions
    void LDX_IMM_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDX_ZP_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDX_ZPY_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDX_ABS_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDX_ABSY_func(CPU& cpu, const Memory& mem, int32& cycles);

    //LDY functions
    void LDY_IMM_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDY_ZP_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDY_ZPX_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDY_ABS_func(CPU& cpu, const Memory& mem, int32& cycles);
    void LDY_ABSX_func(CPU& cpu, const Memory& mem, int32& cycles);

    //STA functions
    void STA_ZP_func(CPU& cpu, Memory& mem, int32& cycles);
    void STA_ZPX_func(CPU& cpu, Memory& mem, int32& cycles);
    void STA_ABS_func(CPU& cpu, Memory& mem, int32& cycles);
    void STA_ABSX_func(CPU& cpu, Memory& mem, int32& cycles);
    void STA_ABSY_func(CPU& cpu, Memory& mem, int32& cycles);
    void STA_INDX_func(CPU& cpu, Memory& mem, int32& cycles);
    void STA_INDY_func(CPU& cpu, Memory& mem, int32& cycles);

    //STX functions
    void STX_ZP_func(CPU& cpu, Memory& mem, int32& cycles);
    void STX_ZPY_func(CPU& cpu, Memory& mem, int32& cycles);
    void STX_ABS_func(CPU& cpu, Memory& mem, int32& cycles);

    //STY functions
    void STY_ZP_func(CPU& cpu, Memory& mem, int32& cycles);
    void STY_ZPX_func(CPU& cpu, Memory& mem, int32& cycles);
    void STY_ABS_func(CPU& cpu, Memory& mem, int32& cycles);

    //Transfer functions
    void TAX_func(CPU& cpu, int32& cycles);
    void TAY_func(CPU& cpu, int32& cycles);
    void TSX_func(CPU& cpu, int32& cycles);
    void TXA_func(CPU& cpu, int32& cycles);
    void TXS_func(CPU& cpu, int32& cycles);
    void TYA_func(CPU& cpu, int32& cycles);

    //Stack functions
    void PHA_func(CPU& cpu, Memory& mem, int32& cycles);
    void PLA_func(CPU& cpu, Memory& mem, int32& cycles);
    void PHP_func(CPU& cpu, Memory& mem, int32& cycles);
    void PLP_func(CPU& cpu, Memory& mem, int32& cycles);
}