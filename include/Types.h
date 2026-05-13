#pragma once
#include <cstdint>

// Standard NES types
using Byte = uint8_t;   // 8-bit
using Word = uint16_t;  // 16-bit
using int32  = int32_t;  // 32-bit
using SByte = int8_t;

namespace Instructions {
    enum Opcode : Byte {

        /*
         * LOAD
         */

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

        /*
         * STORE
         */

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

        /*
         * TRANSFER
         */

        TAX = 0xAA,
        TAY = 0xA8,
        TSX = 0xBA,
        TXA = 0x8A,
        TXS = 0x9A,
        TYA = 0x98,

        /*
         * STACK
         */

        PHA = 0x48,
        PLA = 0x68,
        PHP = 0x08,
        PLP = 0x28,

        /*
         * LOGIC
         */

        //AND
        AND_IMM = 0x29,
        AND_ZP = 0x25,
        AND_ZPX = 0x35,
        AND_ABS = 0x2D,
        AND_ABSX = 0x3D,
        AND_ABSY = 0x39,
        AND_INDX = 0x21,
        AND_INDY = 0x31,

        // EOR (Exclusive OR)
        EOR_IMM  = 0x49,
        EOR_ZP   = 0x45,
        EOR_ZPX  = 0x55,
        EOR_ABS  = 0x4D,
        EOR_ABSX = 0x5D,
        EOR_ABSY = 0x59,
        EOR_INDX = 0x41,
        EOR_INDY = 0x51,

        // ORA (Logical Inclusive OR)
        ORA_IMM  = 0x09,
        ORA_ZP   = 0x05,
        ORA_ZPX  = 0x15,
        ORA_ABS  = 0x0D,
        ORA_ABSX = 0x1D,
        ORA_ABSY = 0x19,
        ORA_INDX = 0x01,
        ORA_INDY = 0x11,


        /*
         * COMPARE
         */

        // CMP (Compare Accumulator)
        CMP_IMM  = 0xC9,
        CMP_ZP   = 0xC5,
        CMP_ZPX  = 0xD5,
        CMP_ABS  = 0xCD,
        CMP_ABSX = 0xDD,
        CMP_ABSY = 0xD9,
        CMP_INDX = 0xC1,
        CMP_INDY = 0xD1,

        // CPX (Compare X Register)
        CPX_IMM  = 0xE0,
        CPX_ZP   = 0xE4,
        CPX_ABS  = 0xEC,

        // CPY (Compare Y Register)
        CPY_IMM  = 0xC0,
        CPY_ZP   = 0xC4,
        CPY_ABS  = 0xCC,

        /*
         * ARITHMETIC
         */

        // ADC - Add with Carry
        ADC_IMM  = 0x69,
        ADC_ZP   = 0x65,
        ADC_ZPX  = 0x75,
        ADC_ABS  = 0x6D,
        ADC_ABSX = 0x7D,
        ADC_ABSY = 0x79,
        ADC_INDX = 0x61,
        ADC_INDY = 0x71,

        // SBC - Subtract with Carry
        SBC_IMM  = 0xE9,
        SBC_ZP   = 0xE5,
        SBC_ZPX  = 0xF5,
        SBC_ABS  = 0xED,
        SBC_ABSX = 0xFD,
        SBC_ABSY = 0xF9,
        SBC_INDX = 0xE1,
        SBC_INDY = 0xF1,

        /*
         * INCREMENT / DECREMENT
         */

        // INC - Increment Memory
        INC_ZP   = 0xE6,
        INC_ZPX  = 0xF6,
        INC_ABS  = 0xEE,
        INC_ABSX = 0xFE,

        // INX - Increment X Register
        INX = 0xE8,

        // INY - Increment Y Register
        INY = 0xC8,

        // DEC - Decrement Memory
        DEC_ZP   = 0xC6,
        DEC_ZPX  = 0xD6,
        DEC_ABS  = 0xCE,
        DEC_ABSX = 0xDE,

        // DEX - Decrement X Register
        DEX = 0xCA,

        // DEY - Decrement Y Register
        DEY = 0x88,

        /*
         * SHIFT
         */

        // ASL - Arithmetic Shift Left
        ASL_ACC  = 0x0A,
        ASL_ZP   = 0x06,
        ASL_ZPX  = 0x16,
        ASL_ABS  = 0x0E,
        ASL_ABSX = 0x1E,

        // LSR - Logical Shift Right
        LSR_ACC  = 0x4A,
        LSR_ZP   = 0x46,
        LSR_ZPX  = 0x56,
        LSR_ABS  = 0x4E,
        LSR_ABSX = 0x5E,

        // ROL - Rotate Left
        ROL_ACC  = 0x2A,
        ROL_ZP   = 0x26,
        ROL_ZPX  = 0x36,
        ROL_ABS  = 0x2E,
        ROL_ABSX = 0x3E,

        // ROR - Rotate Right
        ROR_ACC  = 0x6A,
        ROR_ZP   = 0x66,
        ROR_ZPX  = 0x76,
        ROR_ABS  = 0x6E,
        ROR_ABSX = 0x7E,

        /*
         * JUMP / SUBROUTINE
         */

        // JMP - Jump
        JMP_ABS = 0x4C,
        JMP_IND = 0x6C,

        // JSR - Jump to Subroutine
        JSR_ABS = 0x20,

        // RTS - Return from Subroutine
        RTS = 0x60,

        /*
         * BRANCH
         */

        // BCC - Branch if Carry Clear
        BCC = 0x90,

        // BCS - Branch if Carry Set
        BCS = 0xB0,

        // BEQ - Branch if Equal
        BEQ = 0xF0,

        // BMI - Branch if Minus
        BMI = 0x30,

        // BNE - Branch if Not Equal
        BNE = 0xD0,

        // BPL - Branch if Positive
        BPL = 0x10,

        // BVC - Branch if Overflow Clear
        BVC = 0x50,

        // BVS - Branch if Overflow Set
        BVS = 0x70,

        /*
         * STATUS FLAG
         */

        // CLC - Clear Carry Flag
        CLC = 0x18,

        // CLD - Clear Decimal Mode
        CLD = 0xD8,

        // CLI - Clear Interrupt Disable
        CLI = 0x58,

        // CLV - Clear Overflow Flag
        CLV = 0xB8,

        // SEC - Set Carry Flag
        SEC = 0x38,

        // SED - Set Decimal Flag
        SED = 0xF8,

        // SEI - Set Interrupt Disable
        SEI = 0x78,

        /*
         * SYSTEM
         */

        // BRK - Force Interrupt
        BRK = 0x00,

        // NOP - No Operation
        NOP = 0xEA,

        // RTI - Return from Interrupt
        RTI = 0x40,

        /*
         * BIT TEST
         */

        // BIT - Bit Test
        BIT_ZP  = 0x24,
        BIT_ABS = 0x2C,

    };
}