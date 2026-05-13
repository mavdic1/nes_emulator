#include "Bus.h"

void Bus::Write(Word address, Byte data) {
    // RAM Range (0x0000 - 0x1FFF)
    if (address <= 0x1FFF) {
        ram.Write(address, data);
    }
    // PPU Registers (0x2000 - 0x3FFF)
    else if (address >= 0x2000 && address <= 0x3FFF) {
    }
    // APU and I/O (0x4000 - 0x4017)
    else if (address >= 0x4000 && address <= 0x4017) {
    }
    // Cartridge Space / ROM (0x4020 - 0xFFFF)
    else if (address >= 0x4020) {
        ram.Write(address, data);
    }
}

Byte Bus::Read(Word address) const {
    // RAM Range
    if (address <= 0x1FFF) {
        return ram.Read(address);
    }
    // PPU Range
    else if (address >= 0x2000 && address <= 0x3FFF) {
        return 0x00; // Placeholder for PPU Read
    }
    // ROM Range
    else if (address >= 0x8000) {
        return ram.Read(address);
    }

    return 0x00;
}