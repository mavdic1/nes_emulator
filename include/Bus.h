#pragma once
#include "Types.h"
#include "Memory.h"

struct Bus {
    Memory ram;
    // PPU ppu; // Future addition

    void Write(Word address, Byte data);
    [[nodiscard]] Byte Read(Word address) const;
};