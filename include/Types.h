#pragma once
#include <cstdint>

// Standard NES types
using Byte = uint8_t;   // 8-bit
using Word = uint16_t;  // 16-bit
using u32  = uint32_t;  // 32-bit

namespace Instructions {
    enum Opcode : Byte {
        // LDA - Load Accumulator
        LDA_IMM  = 0xA9,
        LDA_ZP   = 0xA5,
        LDA_ZPX  = 0xB5,
        LDA_ABS  = 0xAD,
        LDA_ABSX = 0xBD,
        LDA_ABSY = 0xB9,
        LDA_INDX = 0xA1,
        LDA_INDY = 0xB1,

        // LDX - Load X Register
        LDX_IMM  = 0xA2,
        LDX_ZP   = 0xA6,
        LDX_ZPY  = 0xB6,
        LDX_ABS  = 0xAE,
        LDX_ABSY = 0xBE,

        // LDY - Load Y Register
        LDY_IMM  = 0xA0,
        LDY_ZP   = 0xA4,
        LDY_ZPX  = 0xB4,
        LDY_ABS  = 0xAC,
        LDY_ABSX = 0xBC,

        // STA - Store Accumulator
        STA_ZP   = 0x85,
        STA_ZPX  = 0x95,
        STA_ABS  = 0x8D,
        STA_ABSX = 0x9D,
        STA_ABSY = 0x99,
        STA_INDX = 0x81,
        STA_INDY = 0x91,

        // STX - Store X Register
        STX_ZP   = 0x86,
        STX_ZPY  = 0x96,
        STX_ABS  = 0x8E,

        // STY - Store Y Register
        STY_ZP   = 0x84,
        STY_ZPX  = 0x94,
        STY_ABS  = 0x8C,

        //Transfer
        TAX = 0xAA,
        TAY = 0xA8,
        TSX = 0xBA,
        TXA = 0x8A,
        TXS = 0x9A,
        TYA = 0x98,

        //Stack
        PHA = 0x48,
        PLA = 0x68,
        PHP = 0x08,
        PLP = 0x28,
    };
}